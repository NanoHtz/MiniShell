/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:04:14 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/23 13:04:14 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*one_ops_more_2: misma gestion que one_ops
*/
int	one_ops_more_2(t_lexer *lxr)
{
	if (lxr->input[lxr->pos] == '&')
	{
		token(lxr, T_ERROR, "&", 1);
		return (1);
	}
	if (lxr->input[lxr->pos] == '(')
	{
		token(lxr, T_ERROR, "(", 1);
		return (1);
	}
	return (0);
}

/*
	*one_ops_more: misma gestion que one_ops
*/
int	one_ops_more(t_lexer *lxr)
{
	if (lxr->input[lxr->pos] == ')')
	{
		token(lxr, T_ERROR, ")", 1);
		return (1);
	}
	if (lxr->input[lxr->pos] == '`')
	{
		token(lxr, T_ERROR, "`", 1);
		return (1);
	}
	if (lxr->input[lxr->pos] == '{')
	{
		token(lxr, T_ERROR, "{", 1);
		return (1);
	}
	if (lxr->input[lxr->pos] == '}')
	{
		token(lxr, T_ERROR, "}", 1);
		return (1);
	}
	return (0);
}

/*
	*one_ops: reconoce y tokeniza operadores simples de un carácter.
	*Si hay coincidencia, token() emite el token y consume 1 carácter.
	*- 1 si se reconoció y gestionó un operador; 0 si no había operador simple.
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
	if (lxr->input[lxr->pos] == ';')
	{
		token(lxr, T_ERROR, ";", 1);
		return (1);
	}
	if (one_ops_more(lxr) == 1)
		return (1);
	if (one_ops_more_2(lxr) == 1)
		return (1);
	return (0);
}
