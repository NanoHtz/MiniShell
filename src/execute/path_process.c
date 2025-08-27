/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:42:25 by pablo             #+#    #+#             */
/*   Updated: 2025/08/23 19:38:30 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

char	**get_env_paths(char **envp)
{
	int		i;
	char	*path_var;
	char	**result;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_var = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			result = ft_split(path_var, ':');
			free(path_var);
			return (result);
		}
		i++;
	}
	return (NULL);
}

char	*try_direct_path(char *cmd)
{
	if (!cmd)
		return (NULL);
	/* Solo es “ruta directa” si el usuario escribió un path (tiene '/') */
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	/* Sin '/', no probar cwd: deja que PATH decida */
	return (NULL);
}


char	*search_in_paths(char *cmd, char **paths)
{
	char		*temp;
	char		*full_path;
	struct stat	sb;
	int			i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0 && stat(full_path, &sb) == 0
			&& S_ISREG(sb.st_mode))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*res;

	res = try_direct_path(cmd);
	if (res)
		return (res);
	paths = get_env_paths(envp);
	if (!paths)
		return (NULL);
	res = search_in_paths(cmd, paths);
	ft_free_split(paths);
	return (res);
}
