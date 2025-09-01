/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:27:58 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/09/01 10:27:58 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

ssize_t	append_name_at(char **out, const char *p,
								char **cmd_env, t_mini *shell)
{
	size_t	len;
	char	*key;
	char	*val;

	len = var_name_len(p);
	key = ft_substr(p, 0, len);
	if (!key)
		return (-1);
	val = get_env_value(key, cmd_env, shell->own_env, shell->env);
	free(key);
	if (xcat_take(out, val) < 0)
		return (-1);
	return ((ssize_t)len);
}
