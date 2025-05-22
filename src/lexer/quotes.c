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

void	change_quote(t_lexer *lxr, int *sq, int *dq)
{
	if (lxr->input[lxr->pos] == '"')
		*dq = !*dq;
	else if (lxr->input[lxr->pos] == '\'')
		*sq = !*sq;
}

int	copy_value(int len, int start, t_lexer *lxr)
{
	char	*value;

	value = malloc(len + 1);
	if (!value)
		return (-1);
	ft_memcpy(value, lxr->input + start, len);
	value[len] = '\0';
	token(lxr, T_WORD, value, 0);
	free(value);
	return (0);
}

int	quotes(t_lexer *lxr, int *dq, int *sq)
{
	int		len;
	int		start;

	if ((lxr->input[lxr->pos] == '"' && *sq == 0)
		|| (lxr->input[lxr->pos] == '\'' && *dq == 0))
	{
		change_quote(lxr, sq, dq);
		lxr->pos++;
		start = lxr->pos;
		while (lxr->input[lxr->pos] != '\0'
			&& lxr->input[lxr->pos] != '"' && lxr->input[lxr->pos] != '\'')
			lxr->pos++;
		len = lxr->pos - start;
		if (copy_value(len, start, lxr) < 0)
			return (-1);
		if ((lxr->input[lxr->pos] == '"') || (lxr->input[lxr->pos] == '\''))
			lxr->pos++;
		change_quote(lxr, sq, dq);
		return (1);
	}
	return (0);
}
