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

//main
typedef struct s_mini
{
	char	**env;
	char	**own_env;
	int		last_status;
}	t_mini;

//lexer
typedef enum e_token_type
{
	T_WORD,//0
	T_PIPE,//1 |
	T_REDIR_IN,//2 <
	T_REDIR_OUT,//3 >
	T_REDIR_APPEND,//4 >>
	T_HEREDOC,//5 <<
	T_QUOTE,//6 '\'' o ""
	T_EOF//12 '\0'
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}	t_token;

typedef struct s_lexer
{
	char		*input;
	size_t		pos;
	t_list		*tokens;
}	t_lexer;

//parser
typedef enum e_redir_type {
	T_RIN,// <
	T_ROUT,// >
	T_RAPPEND,// >>
	T_RHEREDOC,// <<
	T_INVALID // errores
}	t_rtype;

typedef struct s_redir {
	t_rtype			type;
	char			*target;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd {
	char			**av;
	int				ac;
	t_redir			*redirs;
	char			**cmd_env;
	struct s_cmd	*next;
}	t_cmd;

#endif
