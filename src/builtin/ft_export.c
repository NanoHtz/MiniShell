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
	int		idx;

	key = get_key(arg);
	if (!key)
		return ;
	idx = find_key_index(shell->own_env, key);
	if (idx != -1)
		remove_entry(&shell->own_env, idx);
	idx = find_key_index(shell->env, key);
	if (idx != -1)
		replace_entry(shell->env, idx, arg);
	else
		append_entry(&shell->env, arg);
	free(key);
}

static void	export_variable(char *arg, t_mini *shell)
{
	int		idx;
	char	*kv;

	idx = find_key_index(shell->own_env, arg);
	if (idx != -1)
	{
		append_entry(&shell->env, shell->own_env[idx]);
		remove_entry(&shell->own_env, idx);
		return ;
	}
	if (find_key_index(shell->env, arg) == -1)
	{
		kv = ft_strjoin(arg, "=");
		if (!kv)
			return ;
		append_entry(&shell->env, kv);
		free(kv);
	}
}

static void	process_export_arg(char *arg, t_mini *shell, int *had_err)
{
	char	*key;

	if (ft_strchr(arg, '='))
	{
		key = get_key(arg);
		if (!key || !ms_is_valid_ident(key))
		{
			ms_export_err_ident(arg);
			*had_err = 1;
			if (key)
				free(key);
			return ;
		}
		free(key);
		export_keyval(arg, shell);
		return ;
	}
	if (!ms_is_valid_ident(arg))
	{
		ms_export_err_ident(arg);
		*had_err = 1;
		return ;
	}
	export_variable(arg, shell);
}

int	ft_export(char **args, t_mini *shell)
{
	int	i;
	int	had_err;

	i = 1;
	had_err = 0;
	if (!args || !args[1])
	{
		print_export_no_args(shell->env);
		return (0);
	}
	while (args[i])
	{
		process_export_arg(args[i], shell, &had_err);
		i++;
	}
	if (had_err)
		return (1);
	return (0);
}
