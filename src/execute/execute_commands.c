/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:46:12 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/07/21 18:46:12 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/* --- helpers para char** env --- */
static size_t  charpp_len(char **v)
{
    size_t n = 0;
    if (!v) return 0;
    while (v[n]) n++;
    return n;
}

static size_t  keylen(const char *s)
{
    size_t i = 0;
    if (!s) return 0;
    while (s[i] && s[i] != '=') i++;
    return i;
}

static int     same_key(const char *a, const char *b)
{
    size_t ka = keylen(a), kb = keylen(b);
    if (ka != kb) return 0;
    return (strncmp(a, b, ka) == 0);
}

static char  **free_charpp(char **v)
{
    size_t i;
    if (!v) return NULL;
    for (i = 0; v[i]; i++) free(v[i]);
    free(v);
    return NULL;
}

/* Construye envp = base + overlay (overlay tiene prioridad por clave). Duplica todo. */
static char  **build_exec_env(char **base, char **overlay)
{
    size_t nb = charpp_len(base);
    size_t no = charpp_len(overlay);
    size_t cap = nb + no + 1;              /* tamaño máximo posible */
    char **res = (char **)malloc(sizeof(char *) * cap);
    size_t i, j, r = 0;

    if (!res) return NULL;

    /* Copia base */
    for (i = 0; i < nb; i++) {
        res[r] = strdup(base[i]);
        if (!res[r]) return free_charpp(res);
        r++;
    }

    /* Aplica overlay con sobrescritura por clave */
    for (i = 0; i < no; i++) {
        char *ov = overlay[i];
        size_t k = keylen(ov);
        int found = 0;

        if (!ov || k == 0 || ov[k] != '=') {
            /* ignorar entradas raras sin '=' */
            continue;
        }

        for (j = 0; j < r; j++) {
            if (same_key(res[j], ov)) {
                /* reemplazar */
                char *tmp = strdup(ov);
                if (!tmp) return free_charpp(res);
                free(res[j]);
                res[j] = tmp;
                found = 1;
                break;
            }
        }
        if (!found) {
            res[r] = strdup(ov);
            if (!res[r]) return free_charpp(res);
            r++;
        }
    }
    res[r] = NULL;
    return res;
}


void	execute_commands(t_cmd *cmds, t_mini *shell)
{
	int		in_fd;
	pid_t	last_pid;
	t_cmd	*cmd;

	in_fd = 0;
	last_pid = 0;
	cmd = cmds;
	if (g_interrupted)
		g_interrupted = 0;
	if (!(cmd && cmd->av && cmd->av[0]))
	{
		// Aplicar redirecciones en el proceso padre
		if (handle_redirections(cmd) < 0)
			return ;
	}
	while (cmd)
	{
		last_pid = process_command(cmd, &in_fd, shell);
		cmd = cmd->next;
	}
	wait_for_children(last_pid, shell);
}

pid_t	process_command(t_cmd *cmd, int *in_fd, t_mini *shell)
{
	int		fd[2];
	pid_t	pid;
	t_redir *r;

	r = cmd->redirs;
	if (cmd->next && pipe(fd) < 0)
		perror("pipe");
	while (r)
	{
		if (r->type == T_RHEREDOC)
		{
			r->fd = handler_heredoc(r, cmd->cmd_env, shell);
			if (r->fd < 0)
				return (-1);
		}
		r = r->next;
	}
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (g_interrupted)
	{
		free_cmds(cmd); // limpia la lista de comandos
		return (-1);
	}
	else if (pid == 0)
		child_process(cmd, *in_fd, fd, shell);
	else
		parent_process(pid, cmd->next, in_fd, fd);
	return (pid);
}

void	child_process(t_cmd *cmd, int in_fd, int fd[2], t_mini *shell)
{
	// Señales por defecto en el hijo
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	/* 1) Conectar la pipeline primero */
	if (in_fd != 0 && dup2(in_fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("dup2");
		_exit(1);
	}

	if (cmd->next) {
		close(fd[0]); // no lee
		if (dup2(fd[1], STDOUT_FILENO) < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror("dup2");
			_exit(1);
		}
		close(fd[1]);
	}

	/* Cerrar fds heredados que ya no se usan en el hijo */
	if (in_fd != 0)
		close(in_fd);

	/* 2) AHORA aplicar redirecciones en orden */
	if (handle_redirections(cmd) < 0 || g_interrupted) {
		g_interrupted = 0;
		_exit(1);
	}

	/* 3) Si solo hay redirecciones sin comando, salir con éxito */
	if (!cmd->av || !cmd->av[0])
	{
		_exit(0); // éxito - solo redirecciones
	}

	/* 4) Construir envp = shell->env overlaid con cmd->cmd_env */
	char **exec_env = build_exec_env(shell->env, cmd->cmd_env);
	if (!exec_env) {
		perror("minishell: env alloc");
		_exit(127);
	}

	/* 5) BUILTIN EN HIJO (para tuberías/redirs) */
	if (is_builtin(cmd->av[0])) {
		char **saved = shell->env;
		shell->env = exec_env;
		int st = exec_builtin(cmd, shell);
		shell->env = saved;
		free_charpp(exec_env);
		_exit(st);
	}

	/* 6) Ejecutar comando externo */
	if (!cmd->path) {
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->av[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_charpp(exec_env);
		_exit(127);
	}

	/* Si el usuario escribió un path explícito y es un directorio → 126 */
	if (ft_strchr(cmd->av[0], '/')) {
		struct stat sb;
		if (stat(cmd->path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->av[0], 2);
			ft_putendl_fd(": Is a directory", 2);
			free_charpp(exec_env);
			_exit(126);
		}
	}

	execve(cmd->path, cmd->av, exec_env);

	/* Si execve falla */
	int err = errno;
	perror(cmd->av[0]);
	free_charpp(exec_env);

	if (err == EACCES || err == EPERM)
		_exit(126);
	if (err == ENOENT)
		_exit(127);

	_exit(127);
}

void	parent_process(pid_t pid, t_cmd *has_next, int *in_fd, int fd[2])
{
	(void)pid;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (g_interrupted)
	{
		g_interrupted = 0;
		exit(1);
	}
	if (*in_fd)
		close(*in_fd);
	if (has_next)
	{
		close(fd[1]);
		*in_fd = fd[0];
	}
}

void	wait_for_children(pid_t last_pid, t_mini *shell)
{
	int		status;
	pid_t	w;

	w = wait(&status);
	while (w > 0)
	{
		if (w == last_pid)
		{
			if (WIFEXITED(status))
				shell->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				int sig = WTERMSIG(status);

				if (sig == SIGINT)
					write(1, "\n", 1);
				else if (sig == SIGQUIT)
					ft_putendl_fd("Quit (core dumped)", 2);
				shell->last_status = 128 + sig;
			}
		}

		w = wait(&status);
	}
	signal(SIGINT, sigint_prompt_handler);
	signal(SIGQUIT, SIG_IGN);
}
