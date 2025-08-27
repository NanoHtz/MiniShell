/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:26:12 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/19 19:26:12 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*make_token: crea y devuelve un token con tipo y valor opcional.
	*reserva memoria para cada token.
	*asigna tipo de token
	*duplica la cadena y la guarda en value.
	*o lo deja como NULL si esta vacio.
*/
t_token	*make_token(t_token_type type, const char *text)
{
	t_token	*token;

	token = malloc(sizeof * token);
	if (!token)
		return (NULL);
	token->type = type;
	if (text)
	{
		token->value = ft_strdup(text);
		if (!token->value)
		{
			free(token);
			return (NULL);
		}
	}
	else
		token->value = NULL;
	return (token);
}

/*
	*should_skip_token: decide si se salta un token.
	*si es eof o \0 avanza
	*actualiza pos
*/
int	skip_token(t_lexer *lexer, t_token_type type, const char *text, int n)
{
	if (type != T_EOF)
	{
		if (text == NULL)
		{
			lexer->pos += n;
			return (1);
		}
		if (text[0] == '\0' && (type != T_QUOTE && type != T_SQUOTE))
		{
			lexer->pos += n;
			return (1);
		}
	}
	return (0);
}

/*
	*push_token_node: crea el t_token y lo inserta en la lista del lexer.
	*guarda s_before en la estructura del lexer
	*crea un nuevo nodo de la lista y lo añade al final
	*para que al recorrer la lista de tokens este siempre en el orden formado.
*/
int	push_token(t_lexer *lexer, t_token_type type, const char *text)
{
	t_token	*tok;
	t_list	*node;

	tok = make_token(type, text);
	if (!tok)
		return (-1);
	tok->s_before = lexer->sep;
	node = ft_lstnew(tok);
	if (!node)
	{
		free(tok->value);
		free(tok);
		return (-1);
	}
	if (!lexer->tokens)
		lexer->tokens = node;
	else
		ft_lstadd_back(&lexer->tokens, node);
	return (0);
}

/*
	*token: gestiona cada token..
	*Flujo:
	* si esta vacio y no eof, avanza pos y no genera token.,
	* En caso contrario, crea el token y lo añade a la lista de 'lexer'.
	* Al finalizar, avanza 'pos' en 'n' y pone 'sep=0'.

*/
int	token(t_lexer *lexer, t_token_type type, const char *text, int n)
{
	if (skip_token(lexer, type, text, n))
		return (0);
	if (push_token(lexer, type, text) < 0)
		return (-1);
	lexer->pos += n;
	lexer->sep = 0;
	return (0);
}

/*
	*tokenizer:construye tokens recorriendo la funcion caracter a caracter.
	*Cuando realiza una operacion, la propia funcion avanza las casillas,
	*asique tokenicer solo ha de avanzar tras cada operacion,
	*como ha de analizar todo el input, se añade un continue tras cada operacion.
	*Jerarquía de análisis (en este orden):
	*  1) Espacios: se consumen, avanzan el cursor y marcan separador (sep=1).
	*  2) Comillas: si quotes() reconoce un bloque entrecomillado, lo tokeniza.
	*  3) Operadores dobles: two_ops() (p. ej., <<, >>).
	*  4) Operadores simples: one_ops() (p. ej., |, <, >).
	*  5) Palabras: word_token() captura secuencias alfanuméricas y símbolos
	*     permitidos hasta un separador.
	*carácter respetando la jerarquía anterior.
	*Marcador 'sep': indica que estamos en un límite de token; se pone a 1
	*tras consumir espacios para que la siguiente palabra empiece “limpia”.
	*Finalización: cuando llega a '\0', emite explícitamente T_EOF.
*/
void	tokenizer(t_lexer *lxr)
{
	lxr->sep = 1;
	while (lxr->input[lxr->pos] != '\0')
	{
		if (ft_isspace(lxr->input[lxr->pos]))
		{
			lxr->pos++;
			lxr->sep = 1;
			continue ;
		}
		if (quotes(lxr))
			continue ;
		if (two_ops(lxr))
			continue ;
		if (one_ops(lxr))
			continue ;
		if (word_token(lxr))
			continue ;
		lxr->pos++;
	}
	token(lxr, T_EOF, NULL, 0);
}
