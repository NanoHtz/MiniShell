/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:05:45 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/09 19:05:45 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*init_lexer: inicializa la estructura lexer.
	*Hacemos un strdup para copiar el input y trabajar con una copia propia.
	*Inicializa también el cursor (pos=0) y la lista de tokens (NULL).
	*Si 'lexer' o 'input' son NULL, retorna sin realizar cambios.
	*La memoria de 'lexer->input' se libera después en free_lexer().
*/
void	init_lexer(t_lexer *lexer, const char *input)
{
	if (!lexer || !input)
		return ;
	lexer->input = ft_strdup(input);
	lexer->pos = 0;
	lexer->tokens = NULL;
}

/*
	*lexer: inicializa el lexer y lanza la tokenización.
	*tokenizer construye lxr->tokens y añade un T_EOF al final.
*/
void	lexer(t_lexer *lxr, const char *input)
{
	init_lexer(lxr, input);
	tokenizer(lxr);
}
