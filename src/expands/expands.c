/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 11:38:26 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/23 11:38:26 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*toggle_squote: conmuta el estado de comilla simple.
	*Acción: si c es '\'' y no estamos dentro de comillas dobles, invierte *sq.
	*Retorno: 1 si conmutó; 0 en caso contrario.
*/
/*
int	toggle_squote(char c, int *sq, int dq)
{
	if (c == '\'' && !dq)
	{
		*sq = !*sq;
		return (1);
	}
	return (0);
}
*/
/*
	*toggle_dquote: conmuta el estado de comilla doble.
	*Acción: si c es '"' y no estamos dentro de comillas simples, invierte *dq.
	*Retorno: 1 si conmutó; 0 en caso contrario.
*/
/*
int	toggle_dquote(char c, int *dq, int sq)
{
	if (c == '"' && !sq)
	{
		*dq = !*dq;
		return (1);
	}
	return (0);
}
*/

/*
	*find_unquoted_dollar: devuelve un puntero al primer '$' no protegido por
	*comillas simples. Las comillas dobles no bloquean el '$'.
	*Recorre la cadena conmutando estados de comillas y parando en el primer '$'
	*cuando no estamos dentro de comillas simples.
*/
/*
char	*find_unquoted_dollar(const char *s)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (s[i])
	{
		if (toggle_squote(s[i], &sq, dq) || toggle_dquote(s[i], &dq, sq))
		{
			i++;
			continue ;
		}
		if (s[i] == '$' && !sq)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}
*/
/* expande todas las ocurrencias $... en una cadena (para WORD/QUOTE) */
char	*expand_all(const char *s, char **cmd_env, t_mini *shell)
{
	char	*cur;
	char	*next;

	if (!s)
		return (NULL);
	cur = ft_strdup(s);
	if (!cur)
		return (NULL);
	while (find_unquoted_dollar(cur))
	{
		next = look_for_expands(cur, cmd_env, shell);
		if (!next)
		{
			free(cur);
			return (NULL);
		}
		if (ft_strcmp(next, cur) == 0)
		{
			free(next);
			break ;
		}
		free(cur);
		cur = next;
	}
	return (cur);
}

/* devuelve una copia expandida según el tipo de pieza */
char	*expand_piece(t_token_type type, const char *val,
			char **cmd_env, t_mini *shell)
{
	if (type == T_SQUOTE)
		return (ft_strdup(val));
	return (expand_all(val, cmd_env, shell));
}
