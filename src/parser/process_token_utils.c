/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:19:59 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/09/01 10:19:59 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

t_redir	*last_redir_node(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*last_or_self(t_list *candidate, t_list *self)
{
	if (candidate)
		return (candidate);
	return (self);
}

int	add_arg_and_free(t_cmd *cur, char *acc)
{
	if (add_arg(cur, acc) == 1)
	{
		free(acc);
		return (-1);
	}
	free(acc);
	return (0);
}
