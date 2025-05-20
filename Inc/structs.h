/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:44:32 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/16 13:44:32 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum e_token_type
{
	T_WORD,//0
	T_PIPE,//1 |
	T_REDIR_IN,//2 <
	T_REDIR_OUT,//3 >
	T_REDIR_APPEND,//4 >>
	T_HEREDOC,//5 <<
	T_AND_IF,//6 &&
	T_OR_IF,//7 ||
	T_EOF//8 '\0'
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}	t_token;

typedef struct s_lexer
{
	const char	*input;
	size_t		pos;
	t_list		*tokens;
}	t_lexer;

#endif
