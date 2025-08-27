/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabferna <pabferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:00:04 by pabferna          #+#    #+#             */
/*   Updated: 2024/03/23 18:00:04 by pabferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **str, int totalsize)
{
	int	i;

	i = 0;
	while (i < totalsize)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

static char	*word_cpy(const char *s, char c)
{
	int		len;
	int		i;
	char	*str;

	len = 0;
	i = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	arraysize(char const *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (j == 0 && s[i] != c)
		{
			k++;
			j = 1;
		}
		if (s[i] == c && j == 1)
			j = 0;
		i++;
	}
	return (k);
}

char	**ft_split(char const *s, char c)
{
	int		totalsize;
	int		i;
	char	**str;

	i = 0;
	totalsize = arraysize(s, c);
	str = malloc((totalsize + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (i < totalsize)
	{
		while (*s == c)
			s++;
		str[i] = word_cpy(s, c);
		if (!str[i])
			return (ft_free(str, totalsize), NULL);
		s = ft_strchr(s, c);
		i++;
	}
	str[i] = NULL;
	return (str);
}
