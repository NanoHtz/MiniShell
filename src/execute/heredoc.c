/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:41:38 by pablo             #+#    #+#             */
/*   Updated: 2025/08/27 13:26:24 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int hdoc_loop_iter(t_redir *r, char **line, size_t *len, int pipefd[2],
                   char **cmd_env, t_mini *shell)
{
	ssize_t n;
	char	*out;
	char	*work;

	if (write(2, "> ", 2) < 0)
		return (handle_write_error(*line, pipefd));

	n = getline(line, len, stdin);
	if (n < 0)
		return (heredoc_eof_handler(r->target, *line, pipefd));
	if (n > 0 && (*line)[n - 1] == '\n')
		(*line)[n - 1] = '\0';
	if (ft_strcmp(*line, r->target) == 0)
		return (heredoc_delim_found(pipefd));

	//EXPANSION
	work = *line;
	if (r->exp == 0)
	{
		out = expand_line_heredoc(work, cmd_env, shell);
		if (!out)
			return (handle_write_error(*line, pipefd));
	}
	else
		out = work;
	//FIN DE LA EXPANSION
	if (write(pipefd[1], out, ft_strlen(out)) < 0
	 || write(pipefd[1], "\n", 1) < 0)
		return (handle_write_error(out, pipefd));

	if (out != work)
		free(out);
	return (1);
}

int	handler_heredoc(t_redir *r, char **cmd_env, t_mini *shell)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipefd[0]);
		/* run_heredoc_loop AHORA debe aceptar (t_redir*, write_fd, env, shell) */
		run_heredoc_loop(r, pipefd[1], cmd_env, shell);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		close(pipefd[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			close(pipefd[0]);
			g_interrupted = 1;
			shell->last_status = 130; /* <- importante para $? */
			return (-1);
		}
		return (pipefd[0]);
	}
}

void run_heredoc_loop(t_redir *r, int write_fd, char **env, t_mini *shell)
{
    char   *line = NULL;
    size_t  len = 0;
    int     pipefd[2];

    pipefd[1] = write_fd;

    while (1)
    {
        int res = hdoc_loop_iter(r, &line, &len, pipefd, env, shell);
        if (res != 1)
            break;
    }
    free(line);
    close(write_fd);
}


