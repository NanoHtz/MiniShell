/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:35:17 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/20 11:35:17 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	unclosed_quote(t_lexer *lxr, char quote)
{
	if (quote == '\'')
		token(lxr, T_ERROR, "'", 0);
	else
		token(lxr, T_ERROR, "\"", 0);
	return (1);
}

int	copy_value(int len, int start, t_lexer *lxr, int s_q)
{
	char	*value;

	value = malloc(len + 1);
	if (!value)
		return (-1);
	ft_memcpy(value, lxr->input + start, len);
	value[len] = '\0';
	if (s_q == 1)
		token(lxr, T_SQUOTE, value, 0);
	else
		token(lxr, T_QUOTE, value, 0);
	free(value);
	return (0);
}

int	quotes(t_lexer *lxr)
{
	char	quote;
	int		start;
	int		len;
	int		s_q;

	s_q = 0;
	quote = lxr->input[lxr->pos];
	if (quote != '"' && quote != '\'')
		return (0);
	if (quote == '\'')
		s_q = 1;
	start = ++lxr->pos;
	while (lxr->input[lxr->pos] != '\0' && lxr->input[lxr->pos] != quote)
		lxr->pos++;
	if (lxr->input[lxr->pos] == '\0')
		return (unclosed_quote(lxr, quote));
	len = lxr->pos - start;
	if (copy_value(len, start, lxr, s_q) < 0)
		return (-1);
	if (lxr->input[lxr->pos] == quote)
		lxr->pos++;
	return (1);
}
