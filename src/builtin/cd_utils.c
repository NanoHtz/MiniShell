/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:08:47 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/25 17:08:47 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

char	*ms_getenv_dup(t_mini *shell, const char *key)
{
	int		idx;
	char	*eq;

	idx = find_key_index(shell->env, key);
	if (idx < 0)
		return (NULL);
	eq = ft_strchr(shell->env[idx], '=');
	if (!eq)
		return (ft_strdup(""));
	return (ft_strdup(eq + 1));
}

void	ms_setenv(t_mini *shell, const char *key, const char *val)
{
	char		*kv;
	char		*tmp;
	int			idx;
	const char	*value;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return ;
	if (val)
		value = val;
	else
		value = "";
	kv = ft_strjoin(tmp, value);
	free(tmp);
	if (!kv)
		return ;
	idx = find_key_index(shell->env, key);
	if (idx >= 0)
		replace_entry(shell->env, idx, kv);
	else
		append_entry(&shell->env, kv);
	free(kv);
}
