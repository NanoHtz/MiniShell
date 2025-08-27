/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:14:00 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/17 13:14:00 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*two_ops_more: misma funcionalidad que two_ops, para Norminette
*/
int	two_ops_more(t_lexer *lxr)
{
	if (take_two(lxr->input, lxr->pos, '|') == 1)
	{
		token(lxr, T_ERROR, "||", 2);
		return (1);
	}
	if (take_two(lxr->input, lxr->pos, '&') == 1)
	{
		token(lxr, T_ERROR, "&&", 2);
		return (1);
	}
	if (lxr->input[lxr->pos] == '$' && lxr->input[lxr->pos + 1] == '(')
	{
		token(lxr, T_ERROR, "$(", 2);
		return (1);
	}
	if (lxr->input[lxr->pos] == '|' && lxr->input[lxr->pos + 1] == '&')
	{
		token(lxr, T_ERROR, "|&", 2);
		return (1);
	}
	return (0);
}

/*
	*two_ops: reconoce operadores compuestos de tres y dos caracteres,
	*Orden de comprobación:
	*  1) "<<<" y ">>>": no soportados → T_ERROR.
	*  2) "<<": heredoc → T_HEREDOC.
	*  3) ">>": redirección con append → T_REDIR_APPEND.
	*  4) Otros pares conflictivos → delega en two_ops_more().
	*Efectos: si hay coincidencia, emite el token correspondiente y devuelve 1.
	*No modifica lxr->pos directamente; token() consume la longitud detectada.
	*Retorno: 1 si se reconoció algún operador;
	*0 si no hay operadores dobles/triples.
	*Contexto: se invoca desde tokenizer() antes que los operadores simples.
*/
int	two_ops(t_lexer *lxr)
{
	if (take_three(lxr->input, lxr->pos, '<'))
	{
		token(lxr, T_ERROR, "<<<", 3);
		return (1);
	}
	if (take_three(lxr->input, lxr->pos, '>'))
	{
		token(lxr, T_ERROR, ">>>", 3);
		return (1);
	}
	if (take_two(lxr->input, lxr->pos, '<') == 1)
	{
		token(lxr, T_HEREDOC, "<<", 2);
		return (1);
	}
	if (take_two(lxr->input, lxr->pos, '>') == 1)
	{
		token(lxr, T_REDIR_APPEND, ">>", 2);
		return (1);
	}
	if (two_ops_more(lxr) == 1)
		return (1);
	return (0);
}

/*
	*word_token: crea tokens de palabras/comandos.
	*comprueba que el caracter es fin de linea o un delimitador
	*los delimitadores de palabra son: < > |  \ ' ; & ( ) ` o espacio.
	*señala el inicio y avanza hasta delimitador.
	*copia el fragmento y crea el token
	*Libera el buffer temporal.
	*1 si se generó un T_WORD; 0 si el carácter actual era delimitador o '\0'.
*/
int	word_token(t_lexer *lxr)
{
	const char	*in;
	int			start;
	char		*text;

	in = lxr->input;
	if (in[lxr->pos] == '\0' || is_delimiter(in[lxr->pos]))
		return (0);
	start = lxr->pos;
	while (in[lxr->pos] && !is_delimiter(in[lxr->pos]))
		lxr->pos++;
	text = ft_strndup(in + start, lxr->pos - start);
	token(lxr, T_WORD, text, 0);
	free(text);
	return (1);
}
