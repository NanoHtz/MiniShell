/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:10:48 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/25 11:10:48 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*is_valid: comprueba que es una asignacion válida.
	* que el primer elemento sea alfabetico o _
	* que sea alfanumerico o _ los siguientes
*/
int	is_valid(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[i] != '=')
		return (0);
	return (1);
}

/*
	* count_valid_envs: cuenta cuantas asignaciones validas
	* tiene el comando
*/
int	count_valid_envs(char **av)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (av && av[i])
	{
		if (ft_strchr(av[i], '=') && is_valid(av[i]))
			count++;
		i++;
	}
	return (count);
}

/*
	* count_non_env_args: cuenta
*/
int	count_non_env_args(char **av)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (av && av[i])
	{
		if (!ft_strchr(av[i], '=') || !is_valid(av[i]))
			count++;
		i++;
	}
	return (count);
}
