/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_word_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:06:51 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/25 12:06:51 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*grow_argv: asegura espacio para añadir un argumento en cmd->av.
	*Comportamiento:
	*  - Si cmd->av es NULL, reserva un vector de 2 punteros (uno para el
	*    nuevo argumento y otro para el terminador NULL) con ft_calloc.
	*  - Si ya existe, realoca con ft_realloc desde (ac+1) a (ac+2) punteros,
	*    manteniendo el contenido previo.
*/
char	**grow_argv(t_cmd *cmd)
{
	size_t	old_size;
	size_t	new_size;

	if (cmd->av == NULL)
		return ((char **)ft_calloc(2, sizeof(char *)));
	old_size = sizeof(char *) * (cmd->ac + 1);
	new_size = sizeof(char *) * (cmd->ac + 2);
	return (ft_realloc(cmd->av, old_size, new_size));
}

/*
	*add_arg: añade 'value' como nuevo argumento al comando 'cmd'.
	*Flujo:
	* 1) Asegura capacidad para un argumento más (grow_argv).
	* 2) Duplica 'value' y lo coloca en cmd->av[cmd->ac].
	* 3) En caso de fallo al duplicar, libera todo el vector con ft_free_split.
	* 4) Actualiza cmd->ac y repone el terminador NULL.
*/
int	add_arg(t_cmd *cmd, const char *value)
{
	char	**new_av;

	new_av = grow_argv(cmd);
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
	*scan_following_span: recorre tokens contiguos
	*concatenables (WORD/QUOTE/
	*SQUOTE sin separador) a partir de 'it_start',
	*marcando 'had_quote' si
	*aparecen comillas, y dejando en '*last' el
	*último token consumible.
	*No modifica la lista ni reserva memoria.
*/
void	scan_following_span(t_list *it_start, t_list **last, int *had_quote)
{
	t_token	*tok;

	while (it_start)
	{
		tok = (t_token *)it_start->content;
		if (!is_joinable_token(tok))
			break ;
		if (tok->type == T_QUOTE || tok->type == T_SQUOTE)
			*had_quote = 1;
		*last = it_start;
		it_start = it_start->next;
	}
}

/*
	*skip_if_empty_unquoted: omite argumento si la
	*acumulación quedó vacía
	*y no se usaron comillas. Ajusta '*node' para continuar
	*después de 'last'.
*/
int	skip_unquoted(char *acc, int had_quote, t_list **node, t_list *last)
{
	if (acc[0] == '\0' && !had_quote)
	{
		free(acc);
		*node = last->next;
		return (1);
	}
	return (0);
}
