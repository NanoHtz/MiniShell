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
	*make_token:
	*Asigna el tipo de token y copia el valor.
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
	*token:
	*Despues de hacer el token, lo añade a la lista de tipos
	*Crea un nuevo nodo y lo añade al final de la lista
	*ademas avanza ciertas posiciones en la cadena original.
*/
int	token(t_lexer *lexer, t_token_type type, const char *text, int n)
{
	t_token	*token;
	t_list	*node;

	token = make_token(type, text);
	if (!token)
		return (-1);
	node = ft_lstnew(token);
	if (!node)
	{
		free(token->value);
		free(token);
		return (-1);
	}
	if (!lexer->tokens)
		lexer->tokens = node;
	else
		ft_lstadd_back(&lexer->tokens, node);
	lexer->pos += n;
	return (0);
}

/*
	*tokenizer: analiza caracter a caracter toda la linea.
	*En este sentido, tenemos una jerarquia.
	*Primero avanzamos espacios, comillas, operadores dobles, simples y palabras.
	*Utilizamos el continue para no evaluar mas, asi seguimos la jerarquia.
	*Una vez se evalua un caracter y es una comilla, no se evalua nada mas.
	*Al final se añade el nulo
	! -> PARTE CRITICA.
*/
void	tokenizer(t_lexer *lxr)
{
	while (lxr->input[lxr->pos] != '\0')
	{
		if (ft_isspace(lxr->input[lxr->pos]))
		{
			lxr->pos++;
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
