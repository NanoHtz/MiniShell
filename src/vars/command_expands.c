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

char	*expand_command(char *command, char **env)
{
	int		i;
	char	*equal;
	int		len;

	if (!command || !env)
		return (NULL);
	i = 0;
	len = ft_strlen(command);
	while (env[i])
	{
		if (!ft_strncmp(env[i], command, len) && env[i][len] == '=')
		{
			equal = ft_strchr(env[i], '=');
			if (equal)
				return (ft_strdup(equal + 1));
		}
		i++;
	}
	return (NULL);
}

char	*get_env_value(char *key, char **cmd_env, char **own_env, char **envp)
{
	char	*val;

	if (!key)
		return (ft_strdup(""));
	val = expand_command(key, cmd_env);
	if (val)
		return (val);
	val = expand_command(key, own_env);
	if (val)
		return (val);
	val = expand_command(key, envp);
	if (val)
		return (val);
	return (ft_strdup(""));
}

char	*extract_var(char *str, char **cmd_env, t_mini *shell, int *var_len)
{
	char	*var;
	char	*varname;
	char	*value;
	int		j;

	var = ft_strchr(str, '$');
	if (!var || (!ft_isalpha(var[1]) && var[1] != '_'))
		return (NULL);
	j = 1;
	while (var[j] && (ft_isalnum(var[j]) || var[j] == '_'))
		j++;
	varname = ft_substr(var, 1, j - 1);
	value = get_env_value(varname, cmd_env, shell->own_env, shell->env);
	free(varname);
	*var_len = j;
	return (value);
}

char	*look_for_expands(char *str, char **cmd_env, t_mini *shell)
{
	char	*value;
	char	*prefix;
	char	*suffix;
	char	*result;
	int		var_len;

	value = extract_var(str, cmd_env, shell, &var_len);
	if (!value)
		return (ft_strdup(str));
	prefix = ft_substr(str, 0, ft_strchr(str, '$') - str);
	suffix = ft_strdup(ft_strchr(str, '$') + var_len);
	result = ft_strjoin(prefix, value);
	free(prefix);
	free(value);
	prefix = ft_strjoin(result, suffix);
	free(result);
	free(suffix);
	return (prefix);
}

t_cmd	*expand_commands(t_cmd *cmds, t_mini *shell)
{
	t_cmd	*head;
	int		i;
	char	*expanded;

	head = cmds;
	while (head)
	{
		i = 0;
		while (head->av && head->av[i])
		{
			if (ft_strchr(head->av[i], '$'))
			{
				expanded = look_for_expands(head->av[i], head->cmd_env, shell);
				if (!expanded)
					expanded = ft_strdup("");
				free(head->av[i]);
				head->av[i] = expanded;
			}
			i++;
		}
		head = head->next;
	}
	return (cmds);
}
