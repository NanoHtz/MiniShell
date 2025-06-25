/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:46:49 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/30 11:46:49 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
 * Crea un nodo de la lista de redirecciones.
 */
t_redir	*new_redir_node(t_rtype type, const char *target)
{
	t_redir	*r;

	r = malloc(sizeof(*r));
	if (!r)
		return (NULL);
	r->type = type;
	r->target = strdup(target);
	if (!r->target)
	{
		free(r);
		return (NULL);
	}
	r->next = NULL;
	return (r);
}

/*
 * Añade el nodo al final de la lista de redirecciones.
 */
void	add_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir	*it;

	if (!redir)
		return ;
	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		it = cmd->redirs;
		while (it->next)
			it = it->next;
		it->next = redir;
	}
}
/*
	*Comprueba que sea una redireccion.
*/
int	ft_isredir(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_REDIR_APPEND || type == T_HEREDOC);
}
