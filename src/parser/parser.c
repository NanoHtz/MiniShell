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

#include "../../Inc/minishell.h"

int	run_parse(t_list *tokens, t_cmd *head, t_token_type *last, t_mini *shell)
{
	t_cmd	*cur;
	t_list	*node;
	t_token	*tok;
	int		ret;

	*last = T_EOF;
	cur = head;
	node = tokens;
	while (node)
	{
		tok = (t_token *)node->content;
		if (!tok->value)
			break ;
		*last = tok->type;
		ret = process_token(&node, &cur, shell);
		if (ret == -1)
		{
			free_cmds(head);
			return (0);
		}
		if (ret == 0)
			node = node->next;
	}
	return (1);
}

t_cmd	*parser(t_list *tokens, t_mini *shell)
{
	t_cmd			*head;
	t_token_type	last;

	if (!sintax_ops(tokens, shell))
		return (NULL);
	if (!sintax_redir(tokens, shell))
		return (NULL);
	if (!pipe_space_pipe(tokens, shell))
		return (NULL);
	head = new_cmd();
	run_parse(tokens, head, &last, shell);
	if (!check_pipe_end(last, shell))
	{
		free_cmds(head);
		return (NULL);
	}
	return (head);
}
