/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:46:27 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/30 11:46:27 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*Introduce como "argumentos todos los tipos palabras y comillas"
	*Esto puede ser problematico
	! Las comillas deben ser revisadas.
*/
int	handle_word(t_list **node, t_cmd **cur)
{
	t_token	*tok;

	tok = (t_token *)(*node)->content;
	if (tok->type == T_WORD || tok->type == T_QUOTE)
	{
		if (add_arg(*cur, tok->value) == 1)
		{
			fprintf(stderr, "add_arg fallo con valor: %s\n", tok->value);
			return (-1);
		}
		*node = (*node)->next;
		return (1);
	}
	return (0);
}

/*
	*Comprueba si es una redirección y el tipo de redireccion que es
	*Comprueba que despues de la redirección exista algo o salta error
	*Añade la redirección y añade un "target" de esta.
*/
int	handle_redir(t_list **node, t_cmd **cur)
{
	t_token	*tok;
	t_rtype	rt;
	t_token	*targ;

	tok = (t_token *)(*node)->content;
	if (!ft_isredir(tok->type))
		return (0);
	rt = take_type(tok->type);
	if (rt == T_INVALID)
		return (-1);
	*node = (*node)->next;
	if (!*node || !((t_token *)(*node)->content)->value)
	{
		fprintf(stderr, "minishell: syntax error `%s'\n", tok->value);
		return (0);
	}
	targ = (t_token *)(*node)->content;
	if (targ->type != T_WORD && targ->type != T_QUOTE)
	{
		fprintf(stderr, "minishell: syntax error `%s'\n", tok->value);
		return (0);
	}
	add_redir(*cur, new_redir_node(rt, targ->value));
	*node = (*node)->next;
	return (1);
}

/*
	* Lo importante de esta funcion, esque al detectar una pipe
	* crea un nuevo comando, y avanza a el,
	* para seguir con el orden de lo que se ha introducido.
*/
int	handle_pipe(t_list **node, t_cmd **cur)
{
	t_token	*tok;

	tok = (t_token *)(*node)->content;
	if (tok->type != T_PIPE)
		return (0);
	if ((*cur)->ac == 0 && (*cur)->redirs == NULL)
	{
		fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	(*cur)->next = new_cmd();
	*cur = (*cur)->next;
	*node = (*node)->next;
	return (1);
}

/*
	*Procesa el token en funcion del
	*tipo que sea, pipe, redireccion o palabra.
*/
int	process_token(t_list **node, t_cmd **cur)
{
	if (handle_word(node, cur))
		return (1);
	if (handle_redir(node, cur))
		return (1);
	if (handle_pipe(node, cur))
		return (1);
	return (0);
}
