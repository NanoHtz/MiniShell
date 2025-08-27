/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:56:27 by pablo             #+#    #+#             */
/*   Updated: 2025/08/08 01:37:02 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

void	sigint_prompt_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
	g_interrupted = 1;
}
// void	sigint_heredoc_handler(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	g_interrupted = 1;
// }

void	setup_signals(void)
{
	signal(SIGINT, sigint_prompt_handler);
	signal(SIGQUIT, SIG_IGN);
}
