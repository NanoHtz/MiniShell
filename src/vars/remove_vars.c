/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:14:49 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/07/21 12:14:49 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*remove_vars_from_av: elimina las variables de los comandos, en esta
	* parte, un comando tendra asignacion y comando
	* la asignacion no es ejecutable, asique primero ha de ser
	* eliminada, para dejarlo limpio ante la ejecucion.
	* cuenta las asignaciones para reservar memoria
	* despues copia lo av que no son asignaciones en un nuevo comando
	* y libera el anterior
*/
void	remove_vars_from_av(t_cmd *cmd)
{
	char	**new_av;
	int		i;
	int		j;
	int		count;

	count = count_non_env_args(cmd->av);
	new_av = malloc(sizeof(char *) * (count + 1));
	if (!new_av)
		return ;
	i = 0;
	j = 0;
	while (cmd->av && cmd->av[i])
	{
		if (!ft_strchr(cmd->av[i], '=') || !is_valid(cmd->av[i]))
		{
			new_av[j] = ft_strdup(cmd->av[i]);
			j++;
		}
		i++;
	}
	new_av[j] = NULL;
	ft_free_split(cmd->av);
	cmd->av = new_av;
	cmd->ac = j;
}

/*
	*remove_command: borra todos los elementos del comando
	* libera sus av
	* pone en 0 ac
	* y libera su entorno
	* todo en caso de que tenga
*/
void	remove_command(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->av)
	{
		ft_free_split(cmd->av);
		cmd->av = NULL;
	}
	if (cmd->cmd_env)
	{
		ft_free_split(cmd->cmd_env);
		cmd->cmd_env = NULL;
	}
	cmd->ac = 0;
}

/*
	* remove_node: Elimina el nodo del comando ya liberado
*/
void	remove_node(t_cmd **head, t_cmd *target)
{
	t_cmd	*curr;
	t_cmd	*prev;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (curr == target)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free_cmd(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}
