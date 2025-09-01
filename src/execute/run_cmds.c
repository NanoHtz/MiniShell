/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:32:48 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/07/21 18:32:48 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	* count_commands: Cuenta el total de comandos.
*/
int	count_commands(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

/*
	* run_cmds: Cogemos el path del comando, la hemos extraido del loop
	* para ahorrar lineas de codigo.
	* contamos comandos que nos ayudara a la hora de manejar pipes.
	* cogemos el path para cada comando.
	* ejecutamos los comandos.
	todo -> Se ha añadido la comprobacion del builtin
	todo -> asi aseguramos que si es una se ejecute directamente
	todo -> El path solo se obtenia si habia un unico comando.
	todo -> Este cambio añadiendo el builtin ya ha conseguido ejecutarlos bien
*/
static void	set_commands_path(t_cmd *cmds, char **env)
{
	t_cmd	*cur;
	char	*curpath;

	cur = cmds;
	while (cur)
	{
		if (cur->av && cur->av[0])
		{
			curpath = get_command_path(cur->av[0], env);
			cur->path = curpath;
		}
		else
		{
			cur->path = NULL;
			curpath = NULL;
			free(curpath);
		}
		cur = cur->next;
	}
}

void	run_cmds(t_cmd *cmds, t_mini *shell)
{
	int		len;

	if (!cmds->av)
	{
		execute_commands(cmds, shell);
		return ;
	}
	len = count_commands(cmds);
	if (len == 1 && is_builtin(cmds->av[0]) && cmds->redirs == NULL)
	{
		shell->last_status = exec_builtin(cmds, shell);
		return ;
	}
	set_commands_path(cmds, shell->env);
	execute_commands(cmds, shell);
}
