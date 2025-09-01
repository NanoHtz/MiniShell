/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:30:11 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/09/01 10:30:11 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	handle_redirections(t_cmd *cmd)
{
	t_redir		*r;
	int			ret;

	if (!cmd)
		return (0);
	r = cmd->redirs;
	while (r)
	{
		if (r->type == T_RIN)
			ret = redir_read(r);
		else if (r->type == T_ROUT)
			ret = redir_write(r);
		else if (r->type == T_RAPPEND)
			ret = redir_append(r);
		else if (r->type == T_RHEREDOC)
			ret = handle_heredoc_redir(r);
		else
			ret = 0;
		if (ret < 0)
			return (-1);
		r = r->next;
	}
	return (0);
}
