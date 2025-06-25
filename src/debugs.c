/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 08:14:42 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/29 08:14:42 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	debug_print_tokens(t_lexer *lxr)
{
	t_list	*node;
	t_token	*tok;

	printf("********************LEXER Y TOKENIZACIÓN********************\n");
	node = lxr->tokens;
	while (node)
	{
		tok = (t_token *)node->content;
		printf("    - type=%d value='%s'\n", tok->type, tok->value ? tok->value : "(null)");
		node = node->next;
	}
}
void	debug_print_cmds(t_cmd *cmds)
{
	int		i;
	t_cmd	*tmp;

	printf("********************PARSER******************************\n");
	tmp = cmds;
	while (tmp)
	{
		printf("   argc: %d\n", tmp->ac);
		i = 0;
		while (i < tmp->ac)
		{
			printf("   argv: \"%s\"\n", tmp->av[i]);
			i++;
		}
		tmp = tmp->next;
	}
}
void	debug_print_expanded_cmds(t_cmd *cmds)
{
	int		i;
	t_cmd	*tmp;

	printf("********************EXPANSION******************************\n");
	tmp = cmds;
	while (tmp)
	{
		printf("   argc: %d\n", tmp->ac);
		i = 0;
		while (i < tmp->ac)
		{
			printf("   argv: \"%s\"\n", tmp->av[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

void	debug_print_env(char **env, const char *label)
{
	int	i;

	printf("======= %s =======\n", label);
	if (!env)
	{
		printf("(null)\n");
		return ;
	}
	i = 0;
	while (env[i])
	{
		printf("[%d] %s\n", i, env[i]);
		i++;
	}
	printf("===========================\n");
}

void	print_own_env2(char **own_env)
{
	int	i;

	if (!own_env)
	{
		printf("own_env está vacío.\n");
		return ;
	}
	printf("======= own_env =======\n");
	i = 0;
	while (own_env[i])
	{
		printf("own_env[%d] = %s\n", i, own_env[i]);
		i++;
	}
	printf("=======================\n");
}

