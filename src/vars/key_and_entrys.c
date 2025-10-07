/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:10:40 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/25 11:10:40 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

char	*get_key(const char *assign)
{
	char	*equal;
	int		len;

	equal = ft_strchr(assign, '=');
	if (!equal)
		return (NULL);
	len = equal - assign;
	return (ft_substr(assign, 0, len));
}

int	find_key_index(char **env, const char *key)
{
	int		i;
	size_t	key_len;

	if (!env || !key)
		return (-1);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	append_entry(char ***env, const char *assign)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((*env) && (*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while ((*env) && (*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = ft_strdup(assign);
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
}

void	replace_entry(char **env, int index, const char *assign)
{
	free(env[index]);
	env[index] = ft_strdup(assign);
}
