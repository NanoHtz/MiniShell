/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:20:18 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/15 19:20:18 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_mini *shell)
{
	if (!cmd || !cmd->av || !cmd->av[0])
		return (0);
	if (ft_strcmp(cmd->av[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->av[0], "export") == 0)
		return (ft_export(cmd->av, shell));
	else if (ft_strcmp(cmd->av[0], "pwd") == 0)
	{
		ft_pwd();
		return (0);
	}
	else if (ft_strcmp(cmd->av[0], "cd") == 0)
		return (ft_cd(cmd, shell));
	else if (ft_strcmp(cmd->av[0], "env") == 0)
		return (ft_env(cmd, shell->env));
	else if (ft_strcmp(cmd->av[0], "unset") == 0)
		return (ft_unset(cmd, shell->env));
	else if (ft_strcmp(cmd->av[0], "exit") == 0)
		return (ft_exit(cmd, shell));
	return (127);
}

void	builtin(t_cmd *cmds, t_mini *shell)
{
	t_cmd	*cmd;

	cmd = cmds;
	while (cmd)
	{
		if (!cmd->av || cmd->ac == 0 || !cmd->av[0])
		{
			cmd = cmd->next;
			continue ;
		}
		if (is_builtin(cmd->av[0]))
			exec_builtin(cmd, shell);
		else
			fprintf(stderr, "minishell: %s: command not found\n", cmd->av[0]);
		cmd = cmd->next;
	}
}
