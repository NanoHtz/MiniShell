/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:00:28 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/15 20:00:28 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	is_n(char *av)
{
	int	i;

	i = 0;
	if (av[i] == '-')
	{
		i++;
		while (av[i] == 'n')
			i++;
		if (av[i] == '\0')
			return (1);
	}
	return (0);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;
	int	first;

	i = 1;
	n_flag = 0;
	while (cmd->av[i] && is_n(cmd->av[i]))
	{
		n_flag = 1;
		i++;
	}
	first = 1;
	while (cmd->av[i])
	{
		if (!first)
			write(1, " ", 1);
		ft_putstr(cmd->av[i]);
		first = 0;
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
}
