/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_preparser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:25:20 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/24 17:25:20 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	sintax_ops(t_list *toks, t_mini *sh)
{
	t_token	*t;

	if (toks)
	{
		t = (t_token *)toks->content;
		if (t && t->type == T_PIPE)
		{
			syntax_error(sh, "|");
			return (0);
		}
	}
	while (toks)
	{
		t = (t_token *)toks->content;
		if (t->type == T_ERROR)
		{
			syntax_error(sh, t->value);
			return (0);
		}
		toks = toks->next;
	}
	return (1);
}

int	sintax_redir(t_list *toks, t_mini *sh)
{
	t_list	*nx;
	t_token	*t;

	while (toks)
	{
		t = (t_token *)toks->content;
		if (t && ft_isredir(t->type))
		{
			nx = toks->next;
			if (!validate_redir_target(sh, nx))
				return (0);
		}
		toks = toks->next;
	}
	return (1);
}

int	pipe_space_pipe(t_list *toks, t_mini *sh)
{
	t_token	*t1;
	t_token	*t2;

	while (toks)
	{
		t1 = (t_token *)toks->content;
		if (t1 && t1->type == T_PIPE && toks->next)
		{
			t2 = (t_token *)toks->next->content;
			if (t2 && t2->type == T_PIPE)
			{
				syntax_error(sh, "|");
				return (0);
			}
		}
		toks = toks->next;
	}
	return (1);
}

int	check_pipe_end(t_token_type last, t_mini *sh)
{
	if (last == T_PIPE)
	{
		syntax_error(sh, "|");
		return (0);
	}
	return (1);
}
