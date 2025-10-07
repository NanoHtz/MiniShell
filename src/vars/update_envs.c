/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:38:42 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/07/21 12:38:42 by fgalvez-         ###   ########.fr       */
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
