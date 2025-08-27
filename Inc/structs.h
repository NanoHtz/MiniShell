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
# define STRUCTS_H

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
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC,
	T_QUOTE,
	T_SQUOTE,
	T_ERROR,
	T_EOF
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				s_before;
}	t_token;

typedef struct s_lexer
{
	char		*input;
	size_t		pos;
	t_list		*tokens;
	int			sep;
}	t_lexer;

//parser
typedef enum e_redir_type
{
	T_RIN,
	T_ROUT,
	T_RAPPEND,
	T_RHEREDOC,
	T_INVALID
}	t_rtype;

typedef struct s_redir
{
	t_rtype			type;
	int				fd;
	char			*target;
	struct s_redir	*next;
	int				exp;
}	t_redir;

typedef struct s_cmd
{
	char			**av;
	char			*path;
	int				ac;
	int				len;
	t_redir			*redirs;
	char			**cmd_env;
	struct s_cmd	*next;
}	t_cmd;

#endif
