/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 11:38:26 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/23 11:38:26 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

char	*expand_all(const char *s, char **cmd_env, t_mini *shell)
{
	char	*cur;
	char	*next;

	if (!s)
		return (NULL);
	cur = ft_strdup(s);
	if (!cur)
		return (NULL);
	while (find_unquoted_dollar(cur))
	{
		next = look_for_expands(cur, cmd_env, shell);
		if (!next)
		{
			free(cur);
			return (NULL);
		}
		if (ft_strcmp(next, cur) == 0)
		{
			free(next);
			break ;
		}
		free(cur);
		cur = next;
	}
	return (cur);
}

char	*expand_piece(t_token_type type, const char *val,
			char **cmd_env, t_mini *shell)
{
	if (type == T_SQUOTE)
		return (ft_strdup(val));
	return (expand_all(val, cmd_env, shell));
}
