/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:28:12 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/22 13:28:12 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

void	remove_entry(char ***env, int index)
{
	char	**new_env;

	if (!env || !*env)
		return ;
	new_env = copy_env_without_index(*env, index);
	if (!new_env)
		return ;
	free(*env);
	*env = new_env;
}

static void	export_keyval(char *arg, t_mini *shell)
{
	char	*key;
	int		index;

	key = get_key(arg);
	if (!key)
		return ;
	index = find_key_index(shell->env, key);
	if (index != -1)
		replace_entry(shell->env, index, arg);
	else
		append_entry(&shell->env, arg);
	free(key);
}

static void	export_variable(char *arg, t_mini *shell)
{
	int	index;

	index = find_key_index(shell->own_env, arg);
	if (index != -1)
	{
		append_entry(&shell->env, shell->own_env[index]);
		remove_entry(&shell->own_env, index);
	}
}

void	ft_export(char **args, t_mini *shell)
{
	int	i;

	if (!args || !args[1])
	{
		i = 0;
		while (shell->env && shell->env[i])
		{
			printf("declare -x %s\n", shell->env[i]);
			i++;
		}
		return ;
	}
	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			export_keyval(args[i], shell);
		else
			export_variable(args[i], shell);
		i++;
	}
}
