/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:51:16 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/22 15:51:16 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*all_vars: comprueba que todos los argumentos del comando
	* sean declaraciones validas de variables.
*/
int	all_vars(char **av)
{
	int	i;

	i = 0;
	while (av && av[i])
	{
		if (!ft_strchr(av[i], '=') || !is_valid(av[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
	*handle_all_vars: como todos los elementos son validos, actualiza la
	* lista de variables del entorno de la minishell.
	* despues borra el comando entero, puesto que no es ejecutable.
*/
void	handle_all_vars(t_cmd *cmd, t_mini *shell)
{
	int	i;

	i = 0;
	while (cmd->av && cmd->av[i])
	{
		update_env(&shell->own_env, cmd->av[i]);
		i++;
	}
	remove_command(cmd);
}

/*
	*handle_partial_vars: repasa todos los argumentos en busca de una
	*asignacion si la encuentra y es valida, la guarda en la
	*lista de variables del comando, y borra el argumento del comando
*/
void	handle_partial_vars(t_cmd *cmd)
{
	while (cmd->av && cmd->av[0]
		&& ft_strchr(cmd->av[0], '=')
		&& is_valid(cmd->av[0]))
	{
		set_cmd_env(cmd);
		remove_vars_from_av(cmd);
	}
}

/*
	*vars: recorre la lista de todos los comandos realizada por el parser
	* se encarga de comprobar si, todo el comando son
	* declaraciones de variables validas o si solo algun
	* argumento de los comandos
	* lo son, segun una cosa u otra, actua.
*/
t_cmd	*vars(t_cmd *cmds, t_mini *shell)
{
	t_cmd	*head;
	t_cmd	*tmp;

	head = cmds;
	while (head)
	{
		tmp = head->next;
		if (all_vars(head->av))
		{
			handle_all_vars(head, shell);
			remove_node(&cmds, head);
		}
		else
		{
			if (ft_strcmp(head->av[0], "export") != 0
				&& ft_strcmp(head->av[0], "unset") != 0)
				handle_partial_vars(head);
		}
		head = tmp;
	}
	return (cmds);
}
