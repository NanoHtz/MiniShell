/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:23:08 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/25 18:23:08 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	is_valid_dollar_start(unsigned char c)
{
	if (c == '?' || c == '_')
		return (1);
	if (ft_isalpha(c))
		return (1);
	return (0);
}

int	toggle_squote(char c, int *sq, int dq)
{
	if (c == '\'' && !dq)
	{
		*sq = !*sq;
		return (1);
	}
	return (0);
}

int	toggle_dquote(char c, int *dq, int sq)
{
	if (c == '"' && !sq)
	{
		*dq = !*dq;
		return (1);
	}
	return (0);
}

char	*find_unquoted_dollar(const char *s)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (s[i])
	{
		if (toggle_squote(s[i], &sq, dq) || toggle_dquote(s[i], &dq, sq))
		{
			i++;
			continue ;
		}
		if (s[i] == '$' && !sq
			&& is_valid_dollar_start((unsigned char)s[i + 1]))
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*expand(char *command, char **env)
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
