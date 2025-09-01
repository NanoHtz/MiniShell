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

/*
	*validate_redir_target: comprueba que tras una redirección haya un
	*operando válido (palabra o texto entrecomillado).
	*informa del error con el lexema correspondiente o "newline".
*/
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

/*
	*handle_pipe_segment: gestiona la validación al encontrar un '|'.
	*Reglas:
	* 1) Debe haber aparecido un comando antes del '|'.
	* 2) Tras el '|', se permiten pares redirección+operando (validados).
	* 3) Luego debe venir un token “wordish” (inicio de siguiente comando).
*/
// int	handle_pipe_segment(t_list **node, int *saw_cmd,
// 				int *prev_was_redir, t_mini *sh)
// {
// 	t_token	*t;

// 	// if (!*saw_cmd)
// 	// {
// 	// 	syntax_error(sh, "|");
// 	// 	return (0);
// 	// }
// 	// fprintf(stderr, "--------paso por aqui----------\n");
// 	*node = (*node)->next;
// 	if (!consume_redirs_after_pipe(node, sh))
// 		return (0);
// 	if (!*node)
// 		return (error_value_or_newline_ptr(sh, NULL));
// 	t = (t_token *)(*node)->content;
// 	if (!is_wordish(t->type))
// 		return (error_value_or_newline_ptr(sh, t));
// 	*saw_cmd = 0;
// 	*prev_was_redir = 0;
// 	return (1);
// }

/*
	*update_flags_after_token: actualiza las banderas
*/
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
