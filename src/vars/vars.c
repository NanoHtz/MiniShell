/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:51:16 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/22 15:51:16 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

void	remove_vars_from_av(t_cmd *cmd)
{
	char	**new_av;
	int		i;
	int		j;
	int		count;

	count = count_non_env_args(cmd->av);
	new_av = malloc(sizeof(char *) * (count + 1));
	if (!new_av)
		return ;
	i = 0;
	j = 0;
	while (cmd->av && cmd->av[i])
	{
		if (!ft_strchr(cmd->av[i], '=') || !is_valid(cmd->av[i]))
		{
			new_av[j] = ft_strdup(cmd->av[i]);
			j++;
		}
		i++;
	}
	new_av[j] = NULL;
	ft_free_split(cmd->av);
	cmd->av = new_av;
	cmd->ac = j;
}

t_cmd	*prune_empty_cmds(t_cmd *cmds)
{
	t_cmd	*curr;
	t_cmd	*prev;
	t_cmd	*tmp;

	curr = cmds;
	prev = NULL;
	while (curr)
	{
		if (curr->ac == 0 || !curr->av || !curr->av[0])
		{
			tmp = curr->next;
			if (prev)
				prev->next = tmp;
			else
				cmds = tmp;
			free_cmd(curr);
			curr = tmp;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return (cmds);
}

void	handle_all_vars(t_cmd *cmd, t_mini *shell)
{
	int	i;

	i = 0;
	while (cmd->av && cmd->av[i])
	{
		printf("Detectada asignación local: %s\n", cmd->av[i]);
		update_env(&shell->own_env, cmd->av[i]);
		print_own_env2(shell->own_env);
		i++;
	}
	remove_command(cmd);
}

void	handle_partial_vars(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->av && cmd->av[i])
	{
		if (ft_strchr(cmd->av[i], '=') && is_valid(cmd->av[i]))
		{
			set_cmd_env(cmd);
			remove_vars_from_av(cmd);
			break ;
		}
		i++;
	}
}

t_cmd	*vars(t_cmd *cmds, t_mini *shell)
{
	t_cmd	*head;

	head = cmds;
	while (head)
	{
		if (all_vars(head->av))
			handle_all_vars(head, shell);
		else
			handle_partial_vars(head);
		head = head->next;
	}
	return (cmds);
}
