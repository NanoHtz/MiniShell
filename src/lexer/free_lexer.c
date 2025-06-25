/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:03:31 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/25 12:03:31 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*Funcion de limpieza del lexer
*/
void	free_lexer(t_lexer *lxr)
{
	if (lxr->input)
		free(lxr->input);
	if (lxr->tokens)
		clear_tokens(lxr->tokens);
	lxr->tokens = NULL;
}

/*
	*clear_tokens:
	*Libera todos los tokens.
*/
void	clear_tokens(t_list *lst)
{
	t_list	*next;
	t_token	*tok;

	while (lst)
	{
		next = lst->next;
		tok = lst->content;
		free(tok->value);
		free(tok);
		free(lst);
		lst = next;
	}
}
