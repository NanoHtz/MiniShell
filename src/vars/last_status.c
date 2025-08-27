/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:11:31 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/15 17:11:31 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*out;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	out = (char *)malloc(len1 + len2 + 1);
	if (!out)
	{
		free(s1);
		return (NULL);
	}
	if (len1 > 0)
		ft_memcpy(out, s1, len1);
	if (len2 > 0)
		ft_memcpy(out + len1, s2, len2);
	out[len1 + len2] = '\0';
	free(s1);
	return (out);
}

char	*join_free_first(char *a, const char *b)
{
	size_t	la;
	size_t	lb;
	char	*res;

	if (!a || !b)
		return (free(a), NULL);
	la = ft_strlen(a);
	lb = ft_strlen(b);
	res = (char *)malloc(la + lb + 1);
	if (!res)
		return (free(a), NULL);
	ft_memcpy(res, a, la);
	ft_memcpy(res + la, b, lb + 1);
	free(a);
	return (res);
}

int	push_char(char **out, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	*out = join_free_first(*out, buf);
	return (*out == NULL);
}

char	*expand_last_status_in_str(const char *src, int last_status)
{
	char	*status;
	char	*out;
	int		st[3];

	status = ft_itoa(last_status);
	if (!status)
		return (NULL);
	out = ft_strdup("");
	if (!out)
		return (free(status), NULL);
	st[0] = 0;
	st[1] = 0;
	st[2] = 0;
	if (loop_expand(src, &out, status, st) < 0)
		return (free(status), free(out), NULL);
	free(status);
	return (out);
}

int	last_status(char **av)
{
	int		i;
	int		j;
	int		in_squote;
	int		in_dquote;

	i = 0;
	while (av && av[i])
	{
		in_squote = 0;
		in_dquote = 0;
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '\'' && !in_dquote)
				in_squote = !in_squote;
			else if (av[i][j] == '\"' && !in_squote)
				in_dquote = !in_dquote;
			else if (!in_squote && av[i][j] == '$' && av[i][j + 1] == '?')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
