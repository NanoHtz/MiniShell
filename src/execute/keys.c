/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:36:24 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/09/01 10:36:24 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

size_t	charpp_len(char **v)
{
	size_t	n;

	n = 0;
	if (!v)
		return (0);
	while (v[n])
		n++;
	return (n);
}

size_t	keylen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

int	same_key(const char *a, const char *b)
{
	size_t	ka;
	size_t	kb;

	ka = keylen(a);
	kb = keylen(b);
	if (ka != kb)
		return (0);
	return (ft_strncmp(a, b, ka) == 0);
}

int	process_valid_entry(char **res, char *ov, size_t *r)
{
	size_t	j;
	int		found;
	char	*tmp;

	found = 0;
	j = -1;
	while (++j < *r && !found)
	{
		if (same_key(res[j], ov))
		{
			found = 1;
			tmp = ft_strdup(ov);
			if (!tmp)
				return (1);
			free(res[j]);
			res[j] = tmp;
		}
	}
	if (found)
		return (0);
	res[*r] = ft_strdup(ov);
	if (!res[*r])
		return (1);
	(*r)++;
	return (0);
}

int	process_overlay_entries(char **overlay, char **res, size_t no, size_t *r)
{
	size_t	i;
	char	*ov;
	size_t	k;

	i = 0;
	while (i < no)
	{
		ov = overlay[i];
		if (ov)
		{
			k = keylen(ov);
			if (k != 0 && ov[k] == '=')
			{
				if (process_valid_entry(res, ov, r))
					return (1);
			}
		}
		i++;
	}
	return (0);
}
