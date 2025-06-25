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
	* two_ops:
	* Comprueba si el caracter actual y el siguiente son el mismo.
	* Crea el token correspondiente al tipo.
*/
int	two_ops(t_lexer *lxr)
{
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
	return (0);
}

/*
	* one_ops:
	* Comprueba si el caracter actual es especial.
	* Crea el token correspondiente al tipo.
*/
int	one_ops(t_lexer *lxr)
{
	if (lxr->input[lxr->pos] == '<')
	{
		token(lxr, T_REDIR_IN, "<", 1);
		return (1);
	}
	if (lxr->input[lxr->pos] == '>')
	{
		token(lxr, T_REDIR_OUT, ">", 1);
		return (1);
	}
	if (lxr->input[lxr->pos] == '|')
	{
		token(lxr, T_PIPE, "|", 1);
		return (1);
	}
	return (0);
}

/*
	* word_token:
	* Si no es ninguno de los casos anterios, entonces es una palabra.
	* o un comando, el tratamiento en el lexer es el mismo.
	* Comprueba los limites de las palabras(c.especiales o final).
	* Avanza para obtener la longitud y crea una copia.
	*
	! -> posiblemente algunas lineas no sean necesarias:
	! -> text = ft_strndup(in + start, lxr->pos - start);
	! -> token(lxr, T_WORD, strndup(in + start, lxr->pos - start), 0);
	! -> free(text);
	*
	* Al ponerlas se arreglo un leak de memoria.
	* Pero no le encuentro mucho sentido.
	todo -> En caso de añadir escapes, tambien habra de incluirse aqui.
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
