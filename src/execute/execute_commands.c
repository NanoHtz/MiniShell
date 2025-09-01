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

	if (cmd->next && pipe(fd) < 0)
		perror("pipe");
	if (while_redir(cmd, shell) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (g_interrupted)
	{
		free_cmds(cmd);
		return (-1);
	}
	else if (pid == 0)
	{
		child_process(cmd, *in_fd, fd, shell);
	}
	else
		parent_process(pid, cmd->next, in_fd, fd);
	return (pid);
}

void	child_process(t_cmd *cmd, int in_fd, int fd[2], t_mini *shell)
{
	char	**exec_env;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!connect_pipes(in_fd, fd, cmd))
		_exit(1);
	if (!handle_redirections_check(cmd))
		_exit(1);
	if (!cmd->av || !cmd->av[0])
		_exit(0);
	exec_env = build_and_check_env(shell, cmd);
	if (!exec_env)
		_exit(127);
	if (is_builtin(cmd->av[0]))
		handle_builtin(cmd, shell, exec_env);
	if (!cmd->path)
		handle_command_not_found(cmd, exec_env);
	if (ft_strchr(cmd->av[0], '/') && is_directory(cmd->path))
		handle_directory_error(cmd, exec_env);
	execve(cmd->path, cmd->av, exec_env);
	handle_execve_error(cmd->av[0], exec_env);
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
	int		sig;

	w = wait(&status);
	while (w > 0)
	{
		if (w == last_pid)
		{
			if (WIFEXITED(status))
				shell->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
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
