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

/*
	*Inicializacion de un nuevo comando, se inicializa
	cada parte de la struct
*/
t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->av = NULL;
	cmd->ac = 0;
	cmd->redirs = NULL;
	cmd->next = NULL;
	cmd->cmd_env = NULL;
	return (cmd);
}

/*
 * Un selector de las redirecciones, necesaria solamente por la norminette
 */
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

/*
	*Comprueba si existe una pipe al inicio del comenado.
 */
int	check_pipe_start(t_list *toklist)
{
	if (toklist && ((t_token *)toklist->content)->type == T_PIPE)
	{
		fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

/*
	*Comprueba si existe una pipe al final del comenado.
 */
int	check_pipe_end(t_token_type last)
{
	if (last == T_PIPE)
	{
		fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}
