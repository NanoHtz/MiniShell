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

//*!	-> Aún no se han comparado los errores con los errores esperados.
//*!	-> Readline da leaks de memoria que no es necesario corregir.

/*
	*init_mini: inicializa los campos necesarios para la mini.
	*En el futuro podemos ir expandiendola.
	*Se incluye por ejemplo la inicializacion del historial. Using_history es
	*de la biblioteca ermitida de readline, inicializa la estructura de datos
	*necesaria para almacenar el historial.
*/
t_lexer	*init_mini(void)
{
	t_lexer	*lxr;

	lxr = malloc(sizeof * lxr);
	if (!lxr)
	{
		ft_perror(-1);
		return (NULL);
	}
	using_history();
	lxr->tokens = NULL;
	return (lxr);
}

/*
	*loop: genera el bucle donde introduciremos los prompts.
	*readline:Muestra el prompt especificado.
	*Nos permite usar comandos basicos de historial.
	*Por ejemplo usar el comando anterior con la flecha hacia arriba.
	*Reserva memoria con malloc, debemos liberarla las adelante.
	*add_history: añade a la lista de historial la linea introducida.
	*Se llama a lexer
	*Se pueden llamar a mas funciones en el futuro, como parser.
*/
void	loop(t_lexer *lxr)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		lexer(lxr, line);
		free_lexer(lxr);
		free(line);
	}
}

/*
	*clear_history, limpia el historial, para evitar leaks.
	*limpieza general antes de terminar.
*/
void	clear_mini(t_lexer *lxr)
{
	rl_clear_history();
	free(lxr);
}

/*
	*Comprobacion de argumentos + funciones anteriores.
*/
int	main(int ac, char **av)
{
	t_lexer	*lxr;

	(void)av;
	if (ac != 1)
		return (ft_error_args(127));
	lxr = init_mini();
	if (!lxr)
		return (1);
	loop(lxr);
	clear_mini(lxr);
	return (0);
}
