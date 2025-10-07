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

void	init_lexer(t_lexer *lexer, const char *input)
{
	if (!lexer || !input)
		return ;
	lexer->input = ft_strdup(input);
	lexer->pos = 0;
	lexer->tokens = NULL;
}

void	lexer(t_lexer *lxr, const char *input)
{
	init_lexer(lxr, input);
	tokenizer(lxr);
}
