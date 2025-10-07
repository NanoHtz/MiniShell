/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:10:05 by fgalvez-          #+#    #+#             */
/*   Updated: 2024/12/05 15:14:50 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

int	g_interrupted = 0;

void	loop_aux(char *line, t_lexer *lxr, t_mini *shell)
{
	t_cmd	*cmds;

	add_history(line);
	lexer(lxr, line);
	cmds = parser(lxr->tokens, shell);
	cmds = vars(cmds, shell);
	if (!cmds)
	{
		free_loop(lxr, cmds, line);
		return ;
	}
	run_cmds(cmds, shell);
	free_loop(lxr, cmds, line);
}

t_lexer	*init_mini(void)
{
	t_lexer	*lxr;

	lxr = malloc(sizeof * lxr);
	if (!lxr)
	{
		ft_perror(1);
		return (NULL);
	}
	using_history();
	lxr->tokens = NULL;
	return (lxr);
}

void	loop(t_lexer *lxr, t_mini *shell)
{
	char	*line;

	while (1)
	{
		setup_signals();
		g_interrupted = 0;
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (g_interrupted)
			shell->last_status = 130;
		if (g_interrupted && *line == '\0')
		{
			free(line);
			continue ;
		}
		if (!*line)
		{
			free(line);
			continue ;
		}
		loop_aux(line, lxr, shell);
	}
}

void	clear_mini(t_lexer *lxr, t_mini *shell)
{
	rl_clear_history();
	ft_free_split(shell->env);
	free(lxr);
}

int	main(int ac, char **av, char **envp)
{
	t_lexer	*lxr;
	t_mini	shell;

	(void)av;
	shell.last_status = 0;
	shell.env = copy_env(envp);
	ms_fix_shlvl(&shell.env);
	shell.own_env = NULL;
	if (!shell.env)
	{
		perror("minishell");
		return (1);
	}
	if (ac != 1)
		return (ft_error_args(127));
	lxr = init_mini();
	if (!lxr)
		return (1);
	loop(lxr, &shell);
	clear_mini(lxr, &shell);
	return (0);
}
