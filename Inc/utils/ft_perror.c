/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:16:53 by fgalvez-          #+#    #+#             */
/*   Updated: 2024/12/05 13:54:38 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	ft_strendl(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(2, &str[i], 1);
		i++;
	}
	write(2, "\n", 1);
}

int	ft_perror(int n)
{
	const char *str;

	str = strerror(errno);
	write(2, "Minishell: ", 11);
	ft_strendl(str);
	return (n);
}

int	ft_error_args(int n)
{
	write(2, "Minishell: ", 11);
	write(2, "too many arguments\n", 19);
	return (n);
}
