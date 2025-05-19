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

//Better coments extension.
//Se coloca // y justo despues ?,!,*,todo.
//?    -> Para dudas, ?
//!    -> Adertencias, cosas que pueden estar mal.
//todo -> Cambios.
//*    -> Explicaciones.

int	main(int	ac, char **av)//? int ac, char **av, char **envp
{
	t_lexer	*lxr;
	char	*line;

	(void)av;
	if (ac != 1)
		return (ft_error_args(127));
	lxr = malloc(sizeof * lxr);
	if (!lxr)
	{
		free(lxr);
		return (ft_perror(1));
	}
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line != '\0')
			add_history(line);
		lexer(lxr, line);
		free(line);
	}
	rl_clear_history();
	free(lxr);
	return (0);
}
