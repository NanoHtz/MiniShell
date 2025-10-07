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

#include "../../Inc/minishell.h"

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

int	skip_token(t_lexer *lexer, t_token_type type, const char *text, int n)
{
	if (type != T_EOF)
	{
		if (text == NULL)
		{
			lexer->pos += n;
			return (1);
		}
		if (text[0] == '\0' && (type != T_QUOTE && type != T_SQUOTE))
		{
			lexer->pos += n;
			return (1);
		}
	}
	return (0);
}

int	push_token(t_lexer *lexer, t_token_type type, const char *text)
{
	t_token	*tok;
	t_list	*node;

	tok = make_token(type, text);
	if (!tok)
		return (-1);
	tok->s_before = lexer->sep;
	node = ft_lstnew(tok);
	if (!node)
	{
		free(tok->value);
		free(tok);
		return (-1);
	}
	if (!lexer->tokens)
		lexer->tokens = node;
	else
		ft_lstadd_back(&lexer->tokens, node);
	return (0);
}

int	token(t_lexer *lexer, t_token_type type, const char *text, int n)
{
	if (skip_token(lexer, type, text, n))
		return (0);
	if (push_token(lexer, type, text) < 0)
		return (-1);
	lexer->pos += n;
	lexer->sep = 0;
	return (0);
}

void	tokenizer(t_lexer *lxr)
{
	lxr->sep = 1;
	while (lxr->input[lxr->pos] != '\0')
	{
		if (ft_isspace(lxr->input[lxr->pos]))
		{
			lxr->pos++;
			lxr->sep = 1;
			continue ;
		}
		if (quotes(lxr))
			continue ;
		if (two_ops(lxr))
			continue ;
		if (one_ops(lxr))
			continue ;
		if (word_token(lxr))
			continue ;
		lxr->pos++;
	}
	token(lxr, T_EOF, NULL, 0);
}
