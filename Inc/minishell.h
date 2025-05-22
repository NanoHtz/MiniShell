/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:16:53 by fgalvez-          #+#    #+#             */
/*   Updated: 2024/12/05 15:09:58 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs.h"
# include "structs.h"

//main.c
t_lexer	*init_mini(void);
void	loop(t_lexer *lxr);
void	clear_mini(t_lexer *lxr);
//lexer.c
void	lexer(t_lexer *lexer, const char *input);
void	init_lexer(t_lexer *lexer, const char *input);
void	debug_print_tokens(const t_lexer *lxr);
void	free_lexer(t_lexer *lxr);
//tokenizer.c
void	tokenizer(t_lexer *lexer);
int		token(t_lexer *lexer, t_token_type type, const char *text, int n);
t_token	*make_token(t_token_type type, const char *text);
void	clear_tokens(t_list *lst);
//types.c
int		take_two(const char *line, int i, const char op);
int		two_ops(t_lexer *lxr, int dq, int sq);
int		one_ops(t_lexer *lxr, int dq, int sq);
int		word_token(t_lexer *lxr, int dq, int sq);
//quotes.c
int		quotes(t_lexer *lxr, int *dq, int *sq);
int		copy_value(int len, int start, t_lexer *lxr);
void	change_quote(t_lexer *lxr, int *sq, int *dq);
//parser.c
t_cmd	*new_cmd(void);
t_cmd	*parser(t_lexer *lxr);

#endif
