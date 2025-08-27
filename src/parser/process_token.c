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
	*handle_word: agrupa y expande una “palabra”.
	*Si encuentra dos comandos que pueden agruparse, lo hace
	*y la añade como argumento del comando.
	*sin comillas (regla de expansión).
*/
int	handle_word(t_list **node, t_cmd **cur, t_mini *shell)
{
	t_token	*tok;
	char	*acc;
	t_list	*last;
	int		had_quote;

	tok = (t_token *)(*node)->content;
	if (tok->type != T_WORD && tok->type != T_QUOTE && tok->type != T_SQUOTE)
		return (0);
	had_quote = (tok->type == T_QUOTE || tok->type == T_SQUOTE);
	acc = expand_piece(tok->type, tok->value, (*cur)->cmd_env, shell);
	if (!acc)
		return (-1);
	last = *node;
	scan_following_span((*node)->next, &last, &had_quote);
	if (append_span(&acc, (*node)->next, *cur, shell) < 0)
		return (-1);
	if (skip_unquoted(acc, had_quote, node, last))
		return (1);
	if (add_arg(*cur, acc) == 1)
		return (free(acc), -1);
	*node = last->next;
	return (1);
}

/*
	*handle_redir: procesa una redirección y construye su operando completo.
	*Flujo:
	* 1) redir_setup(): valida operador y operando (y avanza '*node').
	* 2) Expande la primera pieza del operando.
	* 3) Concatena piezas contiguas “unibles” (append_span).
	* 4) Crea el nodo de redirección y lo añade al comando actual.
	* 5) Avanza '*node' tras el último token consumido y retorna 1.
	*Retornos: 1 (ok), 0 (sintaxis inválida), -1 (error memoria).
*/

/*
int	handle_redir(t_list **node, t_cmd **cur, t_mini *shell)
{
	t_token	*tok;
	t_rtype	rt;
	char	*acc;
	t_list	*last;
	int		r;

	r = redir_setup(node, &rt, &tok);
	if (r != 1)
		return (r);
	last = span_last_joinable((*node)->next);
	if (!last)
		last = *node;
	int		was_quoted = 0;
	t_list	*p = *node;
	while (p)
	{
		t_token *t = (t_token *)p->content;
		if (t->type == T_QUOTE || t->type == T_SQUOTE)
			was_quoted = 1;
		if (p == last)
			break ;
		p = p->next;
	}
	acc = expand_first_piece_node(*node, *cur, shell);
	if (!acc)
		return (-1);
	if (append_span(&acc, (*node)->next, *cur, shell) < 0)
		return (-1);
	t_redir *rnode = new_redir_node(rt, acc);
	if (rt == T_RHEREDOC)
		rnode->exp = was_quoted ? 1 : 0;
	add_redir(*cur, rnode);
	*node = last->next;
	return (1);
}
*/

/* 1) ¿Alguna pieza del delimitador venía entre comillas? */
static int	span_has_quotes(t_list *start, t_list *last)
{
	t_list	*p;
	t_token	*tok;

	p = start;
	while (p)
	{
		tok = (t_token *)p->content;
		if (tok && (tok->type == T_QUOTE || tok->type == T_SQUOTE))
			return (1);
		if (p == last)
			break ;
		p = p->next;
	}
	return (0);
}

/* 2) Último nodo de redirecciones del comando */
static t_redir	*last_redir_node(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static t_list	*last_or_self(t_list *candidate, t_list *self)
{
	if (candidate)
		return (candidate);
	return (self);
}

int	handle_redir(t_list **node, t_cmd **cur, t_mini *shell)
{
	t_token	*tok;
	t_rtype	rt;
	char	*acc;
	t_list	*last;
	int		r;

	r = redir_setup(node, &rt, &tok);
	if (r != 1)
		return (r);
	last = last_or_self(span_last_joinable((*node)->next), *node);
	acc = expand_first_piece_node(*node, *cur, shell);
	if (!acc)
		return (-1);
	if (append_span(&acc, (*node)->next, *cur, shell) < 0)
		return (-1);
	add_redir(*cur, new_redir_node(rt, acc));
	if (rt == T_RHEREDOC && span_has_quotes(*node, last))
		last_redir_node((*cur)->redirs)->exp = 1;
	else if (rt == T_RHEREDOC)
		last_redir_node((*cur)->redirs)->exp = 0;
	*node = last->next;
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
	*tipo que sea, pipe, redireccion o palabra siguiendo una jerarquia.
*/
int	process_token(t_list **node, t_cmd **cur, t_mini *shell)
{
	if (handle_word(node, cur, shell))
		return (1);
	if (handle_redir(node, cur, shell))
		return (1);
	if (handle_pipe(node, cur))
		return (1);
	return (0);
}
