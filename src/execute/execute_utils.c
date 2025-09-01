/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:50:11 by pabferna          #+#    #+#             */
/*   Updated: 2025/09/01 10:43:59 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

pid_t	while_redir(t_cmd *cmd, t_mini *shell)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (g_interrupted)
			return (-1);
		if (r->type == T_RHEREDOC)
		{
			r->fd = handler_heredoc(r, cmd->cmd_env, shell);
			if (r->fd < 0)
				return (-1);
		}
		r = r->next;
	}
	return (0);
}

void	handle_builtin(t_cmd *cmd, t_mini *shell, char **exec_env)
{
	char	**saved;
	int		st;

	saved = shell->env;
	shell->env = exec_env;
	st = exec_builtin(cmd, shell);
	shell->env = saved;
	free_charpp(exec_env);
	_exit(st);
}

char	**build_and_check_env(t_mini *shell, t_cmd *cmd)
{
	char	**exec_env;

	exec_env = build_exec_env(shell->env, cmd->cmd_env);
	if (!exec_env)
	{
		perror("minishell: env alloc");
		return (NULL);
	}
	return (exec_env);
}

int	connect_pipes(int in_fd, int fd[2], t_cmd *cmd)
{
	if (in_fd != 0 && dup2(in_fd, STDIN_FILENO) < 0)
		return (perror("dup2"), 0);
	if (cmd->next)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			return (perror("dup2"), 0);
		close(fd[1]);
	}
	if (in_fd != 0)
		close(in_fd);
	return (1);
}

char	**free_charpp(char **v)
{
	size_t	i;

	if (!v)
		return (NULL);
	i = 0;
	while (v[i])
	{
		free(v[i]);
		i++;
	}
	free(v);
	return (NULL);
}
