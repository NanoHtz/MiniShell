/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:46:27 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/30 11:46:27 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	handle_word(t_list **node, t_cmd **cur, t_mini *shell)
{
	t_token	*tok;
	char	*acc;
	t_list	*last;
	int		had_quote;

	tok = (t_token *)(*node)->content;
	if (tok->type != T_WORD && tok->type != T_QUOTE && tok->type != T_SQUOTE)
		return (0);
	had_quote = (tok->type == T_QUOTE || tok->type == T_SQUOTE);
	acc = expand_piece(tok->type, tok->value, (*cur)->cmd_env, shell);
	if (!acc)
		return (-1);
	last = *node;
	scan_following_span((*node)->next, &last, &had_quote);
	if (append_span(&acc, (*node)->next, *cur, shell) < 0)
	{
		free(acc);
		return (-1);
	}
	if (skip_unquoted(acc, had_quote, node, last))
		return (1);
	if (add_arg_and_free(*cur, acc) < 0)
		return (-1);
	*node = last->next;
	return (1);
}

static int	span_has_quotes(t_list *start, t_list *last)
{
	t_list	*p;
	t_token	*tok;

	p = start;
	while (p)
	{
		tok = (t_token *)p->content;
		if (tok && (tok->type == T_QUOTE || tok->type == T_SQUOTE))
			return (1);
		if (p == last)
			break ;
		p = p->next;
	}
	return (0);
}

int	handle_redir(t_list **node, t_cmd **cur, t_mini *shell)
{
	t_token	*tok;
	t_rtype	rt;
	char	*acc;
	t_list	*last;
	int		r;

	r = redir_setup(node, &rt, &tok);
	if (r != 1)
		return (r);
	last = last_or_self(span_last_joinable((*node)->next), *node);
	acc = expand_first_piece_node(*node, *cur, shell);
	if (!acc)
		return (-1);
	if (append_span(&acc, (*node)->next, *cur, shell) < 0)
		return (-1);
	add_redir(*cur, new_redir_node(rt, acc));
	free(acc);
	if (rt == T_RHEREDOC && span_has_quotes(*node, last))
		last_redir_node((*cur)->redirs)->exp = 1;
	else if (rt == T_RHEREDOC)
		last_redir_node((*cur)->redirs)->exp = 0;
	*node = last->next;
	return (1);
}

int	handle_pipe(t_list **node, t_cmd **cur)
{
	t_token	*tok;

	tok = (t_token *)(*node)->content;
	if (tok->type != T_PIPE)
		return (0);
	if ((*cur)->ac == 0 && (*cur)->redirs == NULL)
	{
		fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	(*cur)->next = new_cmd();
	*cur = (*cur)->next;
	*node = (*node)->next;
	return (1);
}

int	process_token(t_list **node, t_cmd **cur, t_mini *shell)
{
	if (handle_word(node, cur, shell))
		return (1);
	if (handle_redir(node, cur, shell))
		return (1);
	if (handle_pipe(node, cur))
		return (1);
	return (0);
}
