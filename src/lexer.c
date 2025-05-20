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

#include "../Inc/minishell.h"

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

void	lexer(t_lexer *lxr, const char *input)
{
	init_lexer(lxr, input);
	tokenizer(lxr);
	debug_print_tokens(lxr);
}

void	init_lexer(t_lexer *lexer, const char *input)
{
	if (!lexer || !input)
		return ;
	lexer->input = ft_strdup(input);
	lexer->pos = 0;
	lexer->tokens = NULL;
}
