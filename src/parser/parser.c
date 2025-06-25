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
	*Añade argumentos al comando, lo hace realojando la memoria del char*
	* cada vez que se la llama con la nueva capacidad de memoria
	* copia el valor del nuevo comando
	* aumenta ac en uno
 */
int	add_arg(t_cmd *cmd, const char *value)
{
	char	**new_av;
	size_t	old_size;
	size_t	new_size;

	old_size = sizeof(char *) * (cmd->ac + 1);
	new_size = sizeof(char *) * (cmd->ac + 2);
	new_av = ft_realloc(cmd->av, old_size, new_size);
	if (!new_av)
		return (1);
	cmd->av = new_av;
	cmd->av[cmd->ac] = ft_strdup(value);
	if (!cmd->av[cmd->ac])
	{
		ft_free_split(new_av);
		return (1);
	}
	cmd->ac += 1;
	cmd->av[cmd->ac] = NULL;
	return (0);
}

/*
	*Recorre la lista, comprobando cada node, y procesando el token segun sea
	*comando, pipe o redireccion.
 */
int	run_parse(t_list *tokens, t_cmd *head, t_token_type *last)
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
		ret = process_token(&node, &cur);
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
	*Su objetivo es estructurar las listas de tokens en comandos.
	*Comienza verificando si la primera el primer o el ultimo
	*caracter es una pipe -> error de sintaxis.
	*inicializa una lista de comandos y lanza el parser
 */
t_cmd	*parser(t_list *tokens)
{
	t_cmd			*head;
	t_token_type	last;

	if (!check_pipe_start(tokens))
		return (NULL);
	head = new_cmd();
	run_parse(tokens, head, &last);
	if (!check_pipe_end(last))
	{
		free_cmds(head);
		return (NULL);
	}
	return (head);
}
