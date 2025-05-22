/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:05:45 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/09 19:05:45 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*Funcion de limpieza
*/
void	free_lexer(t_lexer *lxr)
{
	if (lxr->input)
		free(lxr->input);
	if (lxr->tokens)
		clear_tokens(lxr->tokens);
	lxr->tokens = NULL;
}

/*
	*Funcion para comprobar si los tokens han sido guardados y en que orden
*/
void	debug_print_tokens(const t_lexer *lxr)
{
	t_list	*node;
	t_token	*tok;

	node = lxr->tokens;
	printf("[DEBUG LIST] start head=%p\n", (void *)lxr->tokens);
	while (node)
	{
		tok = node->content;
		printf("    - type=%d value='", tok->type);
		if (tok->value)
			printf("%s", tok->value);
		else
			printf("(null)");
		printf("'\n");
		node = node->next;
	}
	printf("[DEBUG LIST] end\n");
}

/*
	*init_lexer: inicializa la estructura lexer.
	*Hacemos un strdup para copiad el input, y trabajar mejor con el.
	*luego lo liberamos en free_lexer
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
	*lexer: llamadas a las funciones anteriores y a la tokenizacion.
*/
void	lexer(t_lexer *lxr, const char *input)
{
	init_lexer(lxr, input);
	tokenizer(lxr);
	debug_print_tokens(lxr);
}
