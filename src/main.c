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


//! Debes instalar la biblioteca readline.
//! sudo apt update.
//! sudo apt install libreadline-dev.
//todo, se ha añadido al makefile, en la compilacion: -lreadline -lncurses.
//todo, se ha elaborado el bucle principal y el prompt.
//? Tengo dudas sobre todo lo que tiene que hacer el historial y los controles del bucle, como debe reaccionar ante cntrol + c ? etc..
//? smo se sale del bucle con cntrol + c
int	main(void)//? int ac, char **av, char **envp
{
	char	*line;
	int		len;

	len = ft_strlen("Prueba de libft");
	ft_error("Prueba de utils");
	printf("Prueba de makefile, ft_strlen: %d\n", len);
	//todo, cambios desde aqui.
	while (1)
	{
		line = readline("minishell$ ");//! readline utiliza malloc, siempre se hace free.
		if (line == NULL)
			break;//* aqui no es necesario free(line), por que seria free(null)
		if (*line != '\0')
			add_history(line);//* Añade line a una estructura interna de readline, la flecha hacia arriba llama al comando anterior.
		free(line);
	}
	return (0);
}

