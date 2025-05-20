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

#include "../Inc/minishell.h"

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

	in = lxr->input;
	if (dq || sq
		|| in[lxr->pos] == '\0'
		|| isspace((unsigned char)in[lxr->pos])
		|| strchr("<>|", in[lxr->pos]) != NULL)
		return (0);
	start = lxr->pos;
	while (in[lxr->pos]
		&& !isspace((unsigned char)in[lxr->pos])
		&& !strchr("<>|", in[lxr->pos]))
	{
		lxr->pos++;
	}
	token(lxr, T_WORD, strndup(in + start, lxr->pos - start), 0);
	return (1);
}
