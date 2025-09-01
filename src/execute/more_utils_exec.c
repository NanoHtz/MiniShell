/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:37:23 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/09/01 10:37:23 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	is_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (1);
	return (0);
}

int	handle_redirections_check(t_cmd *cmd)
{
	if (handle_redirections(cmd) < 0 || g_interrupted)
	{
		g_interrupted = 0;
		return (0);
	}
	return (1);
}

char	**build_exec_env(char **base, char **overlay)
{
	size_t	nb;
	size_t	no;
	char	**res;
	size_t	i;
	size_t	r;

	nb = charpp_len(base);
	no = charpp_len(overlay);
	res = (char **)malloc(sizeof(char *) * (nb + no + 1));
	r = 0;
	if (!res)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		res[r] = ft_strdup(base[i]);
		if (!res[r])
			return (free_charpp(res));
		r++;
		i++;
	}
	if (process_overlay_entries(overlay, res, no, &r))
		return (free_charpp(res));
	res[r] = NULL;
	return (res);
}
