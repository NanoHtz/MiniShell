/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:04:04 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/25 11:04:04 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	is_joinable_token(t_token *tok)
{
	if (!tok || !tok->value)
		return (0);
	if (tok->s_before)
		return (0);
	if (tok->type != T_WORD && tok->type != T_QUOTE && tok->type != T_SQUOTE)
		return (0);
	return (1);
}

int	append_next_piece(char **acc, t_token *tok, t_cmd *cur, t_mini *shell)
{
	char	*piece;
	char	*tmp;

	piece = expand_piece(tok->type, tok->value, cur->cmd_env, shell);
	if (!piece)
	{
		free(*acc);
		return (-1);
	}
	tmp = ft_strjoin(*acc, piece);
	free(*acc);
	free(piece);
	if (!tmp)
		return (-1);
	*acc = tmp;
	return (0);
}

int	append_span(char **acc, t_list *start, t_cmd *cur, t_mini *shell)
{
	t_token	*tok;

	while (start)
	{
		tok = (t_token *)start->content;
		if (!is_joinable_token(tok))
			break ;
		if (append_next_piece(acc, tok, cur, shell) < 0)
			return (-1);
		start = start->next;
	}
	return (0);
}
