/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_preparser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:25:20 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/24 17:25:20 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*sintax_ops: valida errores sintácticos básicos en la secuencia de tokens.
	*Qué comprueba:
	* 1) Que el primer token no sea una tubería ('|'); si lo es, informa error.
	* 2) Que no aparezcan tokens marcados como T_ERROR en ningún punto; si se
	*    encuentra alguno, informa error usando su valor.
*/
int	sintax_ops(t_list *toks, t_mini *sh)
{
	t_token	*t;

	if (toks)
	{
		t = (t_token *)toks->content;
		if (t && t->type == T_PIPE)
		{
			syntax_error(sh, "|");
			return (0);
		}
	}
	while (toks)
	{
		t = (t_token *)toks->content;
		if (t->type == T_ERROR)
		{
			syntax_error(sh, t->value);
			return (0);
		}
		toks = toks->next;
	}
	return (1);
}

/*
	*sintax_redir: valida la sintaxis de redirecciones en la secuencia de tokens.
	*Regla: todo token de redirección debe ir seguido de una palabra o una
	*cadena entrecomillada. Si no hay siguiente token o no es válido, se
	*reporta el error (con el valor o "newline") y se aborta.
*/
int	sintax_redir(t_list *toks, t_mini *sh)
{
	t_list	*nx;
	t_token	*t;

	while (toks)
	{
		t = (t_token *)toks->content;
		if (t && ft_isredir(t->type))
		{
			nx = toks->next;
			if (!validate_redir_target(sh, nx))
				return (0);
		}
		toks = toks->next;
	}
	return (1);
}

/*
	*pipeline_segments: valida la estructura de cada segmento del pipeline.
	*Delegación:
	*  - Cuando encuentra '|', gestiona la validación con handle_pipe_segment().
	*  - En el resto de tokens, actualiza
	* banderas con update_flags_after_token().
*/
int	pipeline_segments(t_list *toks, t_mini *sh)
{
	t_token	*t;
	int		saw_cmd;
	int		prev_was_redir;

	saw_cmd = 0;
	prev_was_redir = 0;
	while (toks)
	{
		t = (t_token *)toks->content;
		if (t->type == T_PIPE)
		{
			if (!handle_pipe_segment(&toks, &saw_cmd, &prev_was_redir, sh))
				return (0);
			continue ;
		}
		update_flags(t->type, &saw_cmd, &prev_was_redir);
		toks = toks->next;
	}
	return (1);
}

/*
	*pipe_space_pipe: detecta el patrón “tubería seguida de tubería” sin
	*comando entre medias (p. ej., “|   |”), y lo reporta como error.
	*Qué hace:
	* 1) Recorre la lista de tokens.
	* 2) Si encuentra un T_PIPE y el siguiente token existe y también es T_PIPE,
	*    llama a syntax_error(sh, "|") y aborta.
*/
int	pipe_space_pipe(t_list *toks, t_mini *sh)
{
	t_token	*t1;
	t_token	*t2;

	while (toks)
	{
		t1 = (t_token *)toks->content;
		if (t1 && t1->type == T_PIPE && toks->next)
		{
			t2 = (t_token *)toks->next->content;
			if (t2 && t2->type == T_PIPE)
			{
				syntax_error(sh, "|");
				return (0);
			}
		}
		toks = toks->next;
	}
	return (1);
}

/*
	*Comprueba si existe una pipe al final del comenado.
 */
int	check_pipe_end(t_token_type last, t_mini *sh)
{
	if (last == T_PIPE)
	{
		syntax_error(sh, "|");
		return (0);
	}
	return (1);
}
