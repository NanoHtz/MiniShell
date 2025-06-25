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

void	update_env(char ***own_env, const char *assign)
{
	char	*key;
	int		index;

	if (!assign || !own_env)
		return ;
	key = get_key(assign);
	if (!key)
		return ;
	index = find_key_index(*own_env, key);
	if (index >= 0)
		replace_entry(*own_env, index, assign);
	else
		append_entry(own_env, assign);
	free(key);
}

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

int	all_vars(char **av)
{
	int	i;

	i = 0;
	while (av && av[i])
	{
		if (!ft_strchr(av[i], '=') || !is_valid(av[i]))
			return (0);
		i++;
	}
	return (1);
}

void	remove_command(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->av)
	{
		ft_free_split(cmd->av);
		cmd->av = NULL;
	}
	if (cmd->cmd_env)
	{
		ft_free_split(cmd->cmd_env);
		cmd->cmd_env = NULL;
	}
	cmd->ac = 0;
}

void	set_cmd_env(t_cmd *cmd)
{
	int	i;
	int	j;
	int	count;

	count = count_valid_envs(cmd->av);
	if (count == 0)
		return ;
	cmd->cmd_env = malloc(sizeof(char *) * (count + 1));
	if (!cmd->cmd_env)
		return ;
	i = 0;
	j = 0;
	while (cmd->av && cmd->av[i])
	{
		if (ft_strchr(cmd->av[i], '=') && is_valid(cmd->av[i]))
			cmd->cmd_env[j++] = ft_strdup(cmd->av[i]);
		i++;
	}
	cmd->cmd_env[j] = NULL;
}
