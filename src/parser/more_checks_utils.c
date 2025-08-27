/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:24:18 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/25 10:24:18 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*consume_redirs_after_pipe: desde el token actual (tras un '|'), consume
	*posibles pares de redirección + operando, validando que el operando sea
	*“wordish”. Avanza *node hasta el primer token no redirección.
*/
int	consume_redirs_after_pipe(t_list **node, t_mini *sh)
{
	t_list	*nx;
	t_token	*n;

	while (*node && is_redir(((t_token *)(*node)->content)->type))
	{
		nx = (*node)->next;
		if (!nx)
			return (error_value_or_newline_strict(sh, NULL));
		n = (t_token *)nx->content;
		if (!(n && is_wordish(n->type)))
			return (error_value_or_newline_strict(sh, n));
		*node = nx->next;
	}
	return (1);
}

/*
	*error_value_or_newline_ptr: informa de error usando el lexema si el puntero
	*existe (aunque sea vacío); si no existe, informa "newline".
	*Uso: para el token inmediatamente después del bloque de redirecciones.
*/
int	error_value_or_newline_ptr(t_mini *sh, t_token *tok)
{
	if (tok && tok->value)
		syntax_error(sh, tok->value);
	else
		syntax_error(sh, "newline");
	return (0);
}

/*
	*error_value_or_newline_strict: informa de error usando el lexema si existe
	*y no está vacío; en caso contrario informa "newline".
	*Uso: para validar operandos de redirección, que no pueden ser vacíos.
*/
int	error_value_or_newline_strict(t_mini *sh, t_token *tok)
{
	if (tok && tok->value && tok->value[0] != '\0')
		syntax_error(sh, tok->value);
	else
		syntax_error(sh, "newline");
	return (0);
}
