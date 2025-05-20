/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:26:12 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/19 19:26:12 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

t_token	*make_token(t_token_type type, const char *text)
{
	t_token	*token;

	token = malloc(sizeof * token);
	if (!token)
		return (NULL);
	token->type = type;
	if (text)
	{
		token->value = ft_strdup(text);
		if (!token->value)
		{
			free(token);
			return (NULL);
		}
	}
	else
		token->value = NULL;
	return (token);
}

int	token(t_lexer *lexer, t_token_type type, const char *text, int n)
{
	t_token	*token;
	t_list	*node;

	token = make_token(type, text);
	if (!token)
		return (-1);
	node = ft_lstnew(token);
	if (!node)
	{
		free(token->value);
		free(token);
		return (-1);
	}
	if (!lexer->tokens)
		lexer->tokens = node;
	else
		ft_lstadd_back(&lexer->tokens, node);
	lexer->pos += n;
	return (0);
}

void	tokenizer(t_lexer *lxr)
{
	int	dq;
	int	sq;

	dq = 0;
	sq = 0;
	while (lxr->input[lxr->pos] != '\0')
	{
		if (quotes(lxr, &dq, &sq))
			continue ;
		if (two_ops(lxr, dq, sq))
			continue ;
		if (one_ops(lxr, dq, sq))
			continue ;
		if (word_token(lxr, dq, sq))
			continue ;
		lxr->pos++;
	}
	token(lxr, T_EOF, NULL, 0);
}
