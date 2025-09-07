/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:39:25 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/25 10:39:25 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	validate_redir_target(t_mini *sh, t_list *nx)
{
	t_token	*n;

	if (!nx)
	{
		syntax_error(sh, "newline");
		return (0);
	}
	n = (t_token *)nx->content;
	if (!(n && (n->type == T_WORD || n->type == T_QUOTE
				|| n->type == T_SQUOTE)))
	{
		if (n && n->value && n->value[0] != '\0')
			syntax_error(sh, n->value);
		else
			syntax_error(sh, "newline");
		return (0);
	}
	return (1);
}

void	update_flags(t_token_type type, int *saw_cmd, int *prev_was_redir)
{
	if (is_redir(type))
		*prev_was_redir = 1;
	else if (is_wordish(type))
	{
		if (*prev_was_redir)
			*prev_was_redir = 0;
		else
			*saw_cmd = 1;
	}
	else
		*prev_was_redir = 0;
}
