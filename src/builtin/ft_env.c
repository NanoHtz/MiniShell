/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:14:04 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/22 13:14:04 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	equal(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void	ft_env(t_cmd *cmd, char **env)
{
	if (cmd ->ac > 1)
	{
		ft_putendl_fd("env: too many arguments", 2);
		return ;
	}
	while (*env)
	{
		if (equal(*env, '='))
			ft_putstrendl(*env);
		env++;
	}
}
