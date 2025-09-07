/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:25:53 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/25 11:25:53 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	redir_setup(t_list **node, t_rtype *rt, t_token **tok)
{
	const char	*op;

	*tok = (t_token *)(*node)->content;
	if (!ft_isredir((*tok)->type))
		return (0);
	*rt = take_type((*tok)->type);
	if (*rt == T_INVALID)
		return (-1);
	op = (*tok)->value;
	*node = (*node)->next;
	if (!redir_expect_operand(node, op, tok))
		return (0);
	return (1);
}

char	*expand_first_piece_node(t_list *node, t_cmd *cur, t_mini *shell)
{
	t_token	*tok;

	tok = (t_token *)node->content;
	return (expand_piece(tok->type, tok->value, cur->cmd_env, shell));
}

t_list	*span_last_joinable(t_list *start)
{
	t_list	*last;
	t_token	*tok;

	last = NULL;
	while (start)
	{
		tok = (t_token *)start->content;
		if (!is_joinable_token(tok))
			break ;
		last = start;
		start = start->next;
	}
	return (last);
}

t_redir	*new_redir_node(t_rtype type, const char *target)
{
	t_redir	*r;

	r = malloc(sizeof(*r));
	if (!r)
		return (NULL);
	r->type = type;
	if (type == T_RHEREDOC)
		r->exp = 1;
	r->exp = 0;
	r->target = ft_strdup(target);
	if (!r->target)
	{
		free(r);
		return (NULL);
	}
	r->next = NULL;
	return (r);
}

void	add_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir	*it;

	if (!redir)
		return ;
	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		it = cmd->redirs;
		while (it->next)
			it = it->next;
		it->next = redir;
	}
}
