/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:39:55 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/21 11:39:55 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	gramática de minishell:

	line       ::= pipeline (("&&" | "||") pipeline)*
	pipeline   ::= command ("|" command)*
	command    ::= WORD* (redir)*
	redir      ::= ("<" | ">" | ">>") WORD
*/

#include "../../Inc/minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	return (cmd);
}

/*
t_cmd	*parser(t_lexer *lxr)
{
	t_cmd	*cmd;
	t_list	*node;
	t_token	*token;
	t_cmd	*head;

	node = lxr->tokens;
	cmd = new_cmd();
	head = cmd;
	token = node->content;
	while (node)
	{
		if (token->type == T_WORD)
		{
			//Añadir token->value a cmd args
		}
		else if (token->type == T_RIN || token->type == T_ROUT
			|| token->type == T_RAPPEND || token->type == T_RHEREDOC)
		{
			//consumir operador, la siguiente word sera el target
		}
		else if (token->type == T_PIPE)
		{
				// 3) cerrar argv actual (añadir NULL),
				// crear cmd->next = new_cmd(), y hacer cmd = cmd->next
		}
		else if (tok->type == T_EOF)
			break;
		node = node->next;
	}
}
*/
