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

/*
	*redir_syntax_err: imprime el error de sintaxis estándar para redirecciones
	*usando el lexema del operador. Retorna 0 para encadenar retornos.
*/
int	redir_syntax_err(const char *op)
{
	fprintf(stderr, "minishell: syntax error `%s'\n", op);
	return (0);
}

/*
	*redir_expect_operand: valida que '*node' apunte a un operando válido
	*(WORD/QUOTE/SQUOTE con value no NULL). En error informa con 'op'.
	*Deja en '*out_tok' el token operando si es correcto.
*/
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

/*
	*Comprueba que sea una redireccion.
*/
int	ft_isredir(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_REDIR_APPEND || type == T_HEREDOC);
}
