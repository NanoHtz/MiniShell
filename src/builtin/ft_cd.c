/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:17:03 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/19 14:17:03 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

void	ft_cd(t_cmd *cmd)
{
	char	*target;

	if (cmd->ac > 2)
		return (perror("cd: too many arguments"));
	if (!cmd->av[1])
	{
		target = getenv("HOME");
		if (!target)
		{
			write(1, "cd: HOME not set", 17);
			return ;
		}
	}
	else
		target = cmd->av[1];
	if (chdir(target) != 0)
		perror("cd");
}
