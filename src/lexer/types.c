/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:14:00 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/17 13:14:00 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

static int	is_delimiter(char c)
{
	return (ft_isspace((unsigned char)c) || ft_strchr("<>|", c) != NULL);
}

int	take_two(const char *line, int i, const char op)
{
	if (line[i] == op && line[i + 1] == op)
		return (1);
	return (0);
}

int	two_ops(t_lexer *lxr, int dq, int sq)
{
	if (dq == 0 && sq == 0)
	{
		if (take_two(lxr->input, lxr->pos, '<') == 1)
		{
			token(lxr, T_HEREDOC, "<<", 2);
			return (1);
		}
		if (take_two(lxr->input, lxr->pos, '>') == 1)
		{
			token(lxr, T_REDIR_APPEND, ">>", 2);
			return (1);
		}
		if (take_two(lxr->input, lxr->pos, '&') == 1)
		{
			token(lxr, T_AND_IF, "&&", 2);
			return (1);
		}
		if (take_two(lxr->input, lxr->pos, '|') == 1)
		{
			token(lxr, T_OR_IF, "||", 2);
			return (1);
		}
	}
	return (0);
}

int	one_ops(t_lexer *lxr, int dq, int sq)
{
	if (dq == 0 && sq == 0)
	{
		if (lxr->input[lxr->pos] == '<')
		{
			token(lxr, T_REDIR_IN, "<", 1);
			return (1);
		}
		if (lxr->input[lxr->pos] == '>')
		{
			token(lxr, T_REDIR_OUT, ">", 1);
			return (1);
		}
		if (lxr->input[lxr->pos] == '|')
		{
			token(lxr, T_PIPE, "|", 1);
			return (1);
		}
	}
	return (0);
}

int	word_token(t_lexer *lxr, int dq, int sq)
{
	const char	*in;
	int			start;
	char		*text;

	in = lxr->input;
	if (dq || sq || in[lxr->pos] == '\0' || is_delimiter(in[lxr->pos]))
		return (0);
	start = lxr->pos;
	while (in[lxr->pos] && !is_delimiter(in[lxr->pos]))
		lxr->pos++;
	text = ft_strndup(in + start, lxr->pos - start);
	token(lxr, T_WORD, strndup(in + start, lxr->pos - start), 0);
	free(text);
	return (1);
}
