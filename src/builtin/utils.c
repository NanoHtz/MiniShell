/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:24:13 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/25 17:24:13 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

char	**dup_env(char **env)
{
	int		n;
	int		i;
	char	**cp;

	n = 0;
	while (env && env[n])
		n++;
	cp = (char **)malloc(sizeof(char *) * (n + 1));
	if (!cp)
		return (NULL);
	i = 0;
	while (i < n)
	{
		cp[i] = ft_strdup(env[i]);
		if (!cp[i])
		{
			cp[i] = NULL;
			return (ft_free_split(cp));
		}
		i++;
	}
	cp[i] = NULL;
	return (cp);
}

void	sort_strings(char **a)
{
	int		i;
	int		j;
	char	*tmp;

	if (!a)
		return ;
	i = 0;
	while (a[i])
	{
		j = i + 1;
		while (a[j])
		{
			if (ft_strcmp(a[i], a[j]) > 0)
			{
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
