/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:49:16 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/30 11:49:16 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->av = NULL;
	cmd->ac = 0;
	cmd->len = 0;
	cmd->redirs = NULL;
	cmd->next = NULL;
	cmd->path = NULL;
	cmd->cmd_env = NULL;
	return (cmd);
}

t_rtype	take_type(t_token_type tt)
{
	if (tt == T_REDIR_IN)
		return (T_RIN);
	if (tt == T_REDIR_OUT)
		return (T_ROUT);
	if (tt == T_REDIR_APPEND)
		return (T_RAPPEND);
	if (tt == T_HEREDOC)
		return (T_RHEREDOC);
	return (T_INVALID);
}

int	is_redir(t_token_type t)
{
	if (t == T_REDIR_IN || t == T_REDIR_OUT
		|| t == T_REDIR_APPEND || t == T_HEREDOC)
		return (1);
	return (0);
}

int	is_wordish(t_token_type t)
{
	if (t == T_WORD || t == T_QUOTE || t == T_SQUOTE)
		return (1);
	return (0);
}
