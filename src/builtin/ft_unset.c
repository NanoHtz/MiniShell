/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:28:21 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/22 13:28:21 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	* validate: valida los argumentos
*/
int	validate(char *av)
{
	int	i;

	if (!av || !av[0])
		return (0);
	if (!ft_isalpha((unsigned char)av[0]) && av[0] != '_')
		return (0);
	i = 1;
	while (av[i])
	{
		if (av[i] != '_' && !ft_isalnum((unsigned char)av[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
	* remove_var: libera variables
*/
static int	env_key_match(char *entry, char *key)
{
	int	klen;

	if (!entry || !key)
		return (0);
	klen = ft_strlen(key);
	return (!ft_strncmp(entry, key, klen) && entry[klen] == '=');
}

void	remove_var(char *key, char **env)
{
	int	i;
	int	j;

	if (!key || !env)
		return ;
	i = 0;
	while (env[i])
	{
		if (env_key_match(env[i], key))
		{
			free(env[i]);
			j = i;
			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
			break ;
		}
		i++;
	}
}

/*
	* ft_unset: comprueba si los argyumentos estan validados
	* si lo estan, los borra
*/
int	ft_unset(t_cmd *cmd, char **env)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (i < cmd->ac)
	{
		if (!validate(cmd->av[i]) || ft_strchr(cmd->av[i], '=')
			|| ft_strchr(cmd->av[i], ' '))
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(cmd->av[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
			remove_var(cmd->av[i], env);
		i++;
	}
	return (status);
}
