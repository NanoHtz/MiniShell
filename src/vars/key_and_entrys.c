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

/*
	* get_key: busca el = de la asignacion
	* retorna todo lo anterior.
*/
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

/*
	* find_key_index: busca la asignacion.
	*compara dentro del entorno si la variable ya existe
	*en caso de que exista, devuelve su posicion dentro de env
	*util si se quiere modificar una asignacion
	*eliminarla(unset etc...)
*/
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

/*
	* append_entry: añade una entrada en el entorno.
	* reserva memoria para todo el nuevo entorno, mas el null + la nueva
	* copia todo el anterior entorno y añade al final la nueva asignacion
*/
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

/*
	* replace_entry: reemplaza la asignacion
	* Libera la asignacion anterior, con el index calculado anteriormente
	* el mismo index, pasa ahora a gtener la nueva asignacion
*/
void	replace_entry(char **env, int index, const char *assign)
{
	free(env[index]);
	env[index] = ft_strdup(assign);
}
