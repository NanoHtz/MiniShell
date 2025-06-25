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

int	validate(char *av)
{
	int	i;

	i = 0;
	if (!ft_isalpha(av[i]) && av[i] != '_')
		return (0);
	while (av[i] != '\0')
	{
		if (av[i] != '_' && !ft_isalnum(av[i]))
			return (0);
		i++;
	}
	return (1);
}

void	remove_var(char *av, char **env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(av);
	while (env[i])
	{
		if (ft_strncmp(env[i], av, len) == 0 && env[i][len] == '=')
		{
			free(env[i]);
			j = i;
			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
			continue ;
		}
		i++;
	}
}

void	ft_unset(t_cmd *cmd, char **env)
{
	int	i;

	i = 1;
	while (i < cmd->ac)
	{
		if (!validate(cmd->av[i]))
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(cmd->av[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			i++;
			continue ;
		}
		remove_var(cmd->av[i], env);
		i++;
	}
}
