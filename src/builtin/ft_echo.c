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
	if (av[i] != '-')
		return (0);
	i++;
	if (av[i] != 'n')
		return (0);
	while (av[i] == 'n')
		i++;
	if (av[i] == '\0')
		return (1);
	return (0);
}

static int	echo_write(const char *s, size_t len)
{
	if (write(1, s, len) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		return (1);
	}
	return (0);
}

static int	echo_newline(void)
{
	if (write(1, "\n", 1) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("write");
		return (1);
	}
	return (0);
}

static void	consume_n_flags(t_cmd *cmd, int *i, int *n_flag)
{
	*n_flag = 0;
	while (cmd->av[*i] && is_n(cmd->av[*i]))
	{
		*n_flag = 1;
		(*i)++;
	}
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;
	int	first;

	i = 1;
	consume_n_flags(cmd, &i, &n_flag);
	first = 1;
	while (cmd->av[i])
	{
		if (!first && echo_write(" ", 1))
			return (1);
		if (echo_write(cmd->av[i], ft_strlen(cmd->av[i])))
			return (1);
		first = 0;
		i++;
	}
	if (!n_flag && echo_newline())
		return (1);
	return (0);
}
