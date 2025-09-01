/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:39:55 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/21 11:39:55 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*run_parse: recorre la lista de tokens y construye/actualiza la lista de
	*comandos del pipeline a partir de ellos.
	*Flujo:
	* 1) Inicializa '*last' con T_EOF y fija 'cur' (comando actual) y 'node'
	*    (puntero al token actual).
	* 2) Itera mientras haya tokens. Si el token no
	*tiene 'value' (p. ej., T_EOF),
	*    finaliza el bucle.
	* 3) Actualiza '*last' con el tipo del token corriente y
	* delega el manejo en
	*    process_token(&node, &cur, shell), que puede consumir tokens y/o crear/
	*    modificar nodos de comando.
	* 4) Si process_token devuelve -1, libera 'head' y retorna 0 (error).
	* 5) Si devuelve 0, el token no fue consumido por process_token, así que se
	*    avanza manualmente a node->next. Si devuelve 1, process_token ya movió
	*    'node' y no se toca aquí.
*/
int	run_parse(t_list *tokens, t_cmd *head, t_token_type *last, t_mini *shell)
{
	t_cmd	*cur;
	t_list	*node;
	t_token	*tok;
	int		ret;

	*last = T_EOF;
	cur = head;
	node = tokens;
	while (node)
	{
		tok = (t_token *)node->content;
		if (!tok->value)
			break ;
		*last = tok->type;
		ret = process_token(&node, &cur, shell);
		if (ret == -1)
		{
			free_cmds(head);
			return (0);
		}
		if (ret == 0)
			node = node->next;
	}
	return (1);
}

/*
	*parser: construye la lista de comandos (pipeline) a partir de los tokens.
	*Qué hace:
	* 1) Ejecuta validaciones sintácticas previas sobre la lista de tokens:
	*    operadores, redirecciones y tuberías (inicio, separación y segmentos).
	* 2) Si alguna validación falla, retorna NULL
	* 3) Crea el nodo cabeza con new_cmd() para acumular el primer comando.
	* 4) Invoca run_parse() para rellenar 'head' a partir de 'tokens' y deja
	*    en 'last' el tipo del último token significativo procesado.
	* 5) Verifica que el pipeline no termina en tubería con check_pipe_end();
	*    si falla, libera 'head' y retorna NULL.
*/
t_cmd	*parser(t_list *tokens, t_mini *shell)
{
	t_cmd			*head;
	t_token_type	last;

	if (!sintax_ops(tokens, shell))
		return (NULL);
	if (!sintax_redir(tokens, shell))
		return (NULL);
	if (!pipe_space_pipe(tokens, shell))
		return (NULL);
	head = new_cmd();
	run_parse(tokens, head, &last, shell);
	if (!check_pipe_end(last, shell))
	{
		free_cmds(head);
		return (NULL);
	}
	return (head);
}
