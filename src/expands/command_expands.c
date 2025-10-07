/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_expands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:33:20 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/23 13:33:20 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

char	*get_env_value(char *key, char **cmd_env, char **own_env, char **envp)
{
	char	*val;

	if (!key)
		return (ft_strdup(""));
	val = expand(key, cmd_env);
	if (val)
		return (val);
	val = expand(key, own_env);
	if (val)
		return (val);
	val = expand(key, envp);
	if (val)
		return (val);
	return (ft_strdup(""));
}

char	*handle_qmark(t_mini *shell, int *var_len)
{
	char	*value;

	value = ft_itoa(shell->last_status);
	if (!value)
		return (NULL);
	*var_len = 2;
	return (value);
}

char	*extract_named_var(const char *var, int j,
				t_mini *shell, int *var_len)
{
	char	*varname;
	char	*value;

	varname = ft_substr(var, 1, j - 1);
	if (!varname)
		return (NULL);
	value = get_env_value(varname, NULL, shell->own_env, shell->env);
	free(varname);
	*var_len = j;
	return (value);
}

int	scan_var_name(const char *var)
{
	int	j;

	j = 1;
	while (var[j] && (ft_isalnum((unsigned char)var[j]) || var[j] == '_'))
		j++;
	return (j);
}

char	*extract_var(char *str, char **cmd_env, t_mini *shell, int *var_len)
{
	char	*var;
	int		j;

	(void)cmd_env;
	var = find_unquoted_dollar(str);
	if (!var)
		return (NULL);
	if (var[1] == '?')
		return (handle_qmark(shell, var_len));
	if (!is_valid_dollar_start(var[1]))
		return (NULL);
	j = scan_var_name(var);
	return (extract_named_var(var, j, shell, var_len));
}
