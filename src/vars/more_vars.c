/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:36:32 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/26 18:36:32 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	is_quote_char(char ch, int sq, int dq)
{
	return ((ch == '\'' && !dq) || (ch == '\"' && !sq));
}

void	toggle_quotes(char ch, int *sq, int *dq)
{
	if (ch == '\'' && !*dq)
		*sq = !*sq;
	else if (ch == '\"' && !*sq)
		*dq = !*dq;
}

int	should_expand(const char *s, int i, int sq)
{
	return (!sq && s[i] == '$' && s[i + 1] == '?');
}

int	join_status(char **out, const char *status)
{
	*out = join_free_first(*out, status);
	return (*out == NULL);
}

int	loop_expand(const char *src, char **out,
	const char *status, int st[3])
{
	while (src[st[0]])
	{
		if (is_quote_char(src[st[0]], st[1], st[2]))
		{
			toggle_quotes(src[st[0]], &st[1], &st[2]);
			if (push_char(out, src[st[0]]))
				return (-1);
			st[0]++;
		}
		else if (should_expand(src, st[0], st[1]))
		{
			if (join_status(out, status))
				return (-1);
			st[0] += 2;
		}
		else
		{
			if (push_char(out, src[st[0]]))
				return (-1);
			st[0]++;
		}
	}
	return (0);
}
