/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:24:04 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/09/01 10:24:04 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

char	*join_free(char *a, char *b)
{
	char	*res;

	res = ft_strjoin(a, b);
	free(a);
	free(b);
	return (res);
}

int	needs_process(const char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '$' || *s == '\'' || *s == '"')
			return (1);
		s++;
	}
	return (0);
}

char	*cat_free_left(char *left, const char *right)
{
	char	*cat;

	cat = ft_strjoin(left, right);
	free(left);
	return (cat);
}

int	xcat_take(char **dst, char *right)
{
	char	*cat;

	if (!right)
		return (-1);
	cat = ft_strjoin(*dst, right);
	free(*dst);
	free(right);
	if (!cat)
		return (-1);
	*dst = cat;
	return (1);
}

size_t	var_name_len(const char *p)
{
	size_t	i;

	i = 0;
	while (p[i] && (ft_isalnum((unsigned char)p[i]) || p[i] == '_'))
		i++;
	return (i);
}
