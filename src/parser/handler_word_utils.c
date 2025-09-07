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
