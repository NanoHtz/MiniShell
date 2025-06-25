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
