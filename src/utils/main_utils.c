/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 09:47:03 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/09/02 09:47:03 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

void	cleanup_and_exit(t_mini *shell, t_lexer *lxr)
{
	write(1, "exit\n", 5);
	free_lexer(lxr);
	exit(shell->last_status);
}
