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

/*
	Debe mostrar error de comando no encontrado.
*/
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	exec_builtin(t_cmd *cmd, t_mini *shell)
{
	if (ft_strcmp(cmd->av[0], "echo") == 0)
		ft_echo(cmd);
	if (ft_strcmp(cmd->av[0], "pwd") == 0)
		ft_pwd();
	if (ft_strcmp(cmd->av[0], "cd") == 0)
		ft_cd(cmd);
	if (ft_strcmp(cmd->av[0], "exit") == 0)
		ft_exit(cmd);
	if (ft_strcmp(cmd->av[0], "env") == 0)
		ft_env(cmd, shell->env);
	if (ft_strcmp(cmd->av[0], "unset") == 0)
		ft_unset(cmd, shell->env);
	if (ft_strcmp(cmd->av[0], "export") == 0)
		ft_export(cmd->av, shell);
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
