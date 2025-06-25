/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:28:46 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/21 15:28:46 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	ft_exit(t_cmd *cmd)
{
	int	code;

	ft_putendl_fd("exit", 1);
	code = 0;
	if (cmd->ac == 1)
		exit(0);
	if (!ft_isnum(cmd->av[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd->av[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	if (cmd->ac > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	code = ft_atoi(cmd->av[1]);
	exit((unsigned char)code);
}
