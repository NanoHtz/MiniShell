/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:46:49 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/30 11:46:49 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	redir_syntax_err(const char *op)
{
	fprintf(stderr, "minishell: syntax error `%s'\n", op);
	return (0);
}

int	redir_expect_operand(t_list **node, const char *op, t_token **out_tok)
{
	t_token	*tok;

	if (!*node || !((t_token *)(*node)->content)->value)
		return (redir_syntax_err(op));
	tok = (t_token *)(*node)->content;
	if (tok->type != T_WORD && tok->type != T_QUOTE && tok->type != T_SQUOTE)
		return (redir_syntax_err(op));
	*out_tok = tok;
	return (1);
}

int	ft_isredir(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_REDIR_APPEND || type == T_HEREDOC);
}
