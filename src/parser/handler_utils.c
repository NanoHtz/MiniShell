/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:04:04 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/25 11:04:04 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*is_joinable_token: indica si un token puede concatenarse con el anterior
	*en la misma “palabra” (mismo contexto, sin separador y
	de tipo WORD/QUOTE/SQUOTE).
	*Retorno: 1 si es concatenable; 0 en caso contrario.
*/
int	is_joinable_token(t_token *tok)
{
	if (!tok || !tok->value)
		return (0);
	if (tok->s_before)
		return (0);
	if (tok->type != T_WORD && tok->type != T_QUOTE && tok->type != T_SQUOTE)
		return (0);
	return (1);
}

/*
	*append_next_piece: expande 'tok' y lo concatena a '*acc'.
	*Memoria: libera '*acc' y la pieza intermedia; en error deja
	'*acc' liberado.
	*Retorno: 0 en éxito; -1 en fallo (con '*acc' ya liberado).
*/
int	append_next_piece(char **acc, t_token *tok, t_cmd *cur, t_mini *shell)
{
	char	*piece;
	char	*tmp;

	piece = expand_piece(tok->type, tok->value, cur->cmd_env, shell);
	if (!piece)
	{
		free(*acc);
		return (-1);
	}
	tmp = ft_strjoin(*acc, piece);
	free(*acc);
	free(piece);
	if (!tmp)
		return (-1);
	*acc = tmp;
	return (0);
}

/*
	*append_span: concatena en '*acc' todas las piezas
	*expandibles desde 'start'
	*mientras sean concatenables (WORD/QUOTE/SQUOTE
	*sin separador).
	*Usa expand_piece(...) y ft_strjoin(...) vía
	*append_next_piece(...).
	*Retorno: 0 en éxito; -1 si falla cualquier
	*expansión/concatenación.
	*Nota: si falla, puede haber liberado '*acc'
	*(igual que el flujo original).
*/
int	append_span(char **acc, t_list *start, t_cmd *cur, t_mini *shell)
{
	t_token	*tok;

	while (start)
	{
		tok = (t_token *)start->content;
		if (!is_joinable_token(tok))
			break ;
		if (append_next_piece(acc, tok, cur, shell) < 0)
			return (-1);
		start = start->next;
	}
	return (0);
}
