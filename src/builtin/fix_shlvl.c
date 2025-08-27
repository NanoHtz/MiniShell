/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:56:39 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/20 10:56:39 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

static int	ms_is_number(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	if (s[0] == '+' || s[0] == '-')
		s++;
	i = 0;
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ms_fix_shlvl(char ***penv)
{
	int		idx;
	char	*eq;
	int		n;
	char	*newv;
	char	*line;

	idx = find_key_index(*penv, "SHLVL");
	if (idx == -1)
	{
		append_entry(penv, "SHLVL=1");
		return ;
	}
	eq = ft_strchr((*penv)[idx], '=');
	n = 1;
	if (eq && ms_is_number(eq + 1))
		n = ft_atoi(eq + 1) + 1;
	newv = ft_itoa(n);
	if (!newv)
		return ;
	line = ft_strjoin("SHLVL=", newv);
	free(newv);
	if (!line)
		return ;
	replace_entry(*penv, idx, line);
	free(line);
}
