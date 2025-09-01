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

void	cleanup_and_exit(t_mini *shell, t_lexer *lxr)
{
	free_lexer(lxr);
	exit(shell->last_status);
}

//*!	-> Aún no se han comparado los errores con los errores esperados.
//*!	-> Readline da leaks de memoria que no es necesario corregir.
/*
	*init_mini: inicializa los campos necesarios para la mini.
	*En el futuro podemos ir expandiendola.
	*Se incluye por ejemplo la inicializacion del historial. Using_history es
	*de la biblioteca permitida de readline, inicializa la estructura de datos
	*necesaria para almacenar el historial.
*/
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

/*
	*loop: genera el bucle donde introduciremos los prompts.
	*readline:Muestra el prompt especificado.
	*Nos permite usar comandos basicos de historial.
	*Por ejemplo usar el comando anterior con la flecha hacia arriba.
	*Reserva memoria con malloc, debemos liberarla mas adelante.
	*add_history: añade a la lista de historial la linea introducida.
	*Se llama a lexer, expand y parser, a la creacion de variables
	*a la expansion de comandos
	! se debe añadir la variable $?.
	*Se pueden llamar a mas funciones en el futuro.
	*Se liberan algunos elementos.
	builtin(cmds, shell); -> poner esto si existe algun error.
*/
void	loop(t_lexer *lxr, t_mini *shell)
{
	char	*line;
	t_cmd	*cmds;

	while (1)
	{
		setup_signals();
		g_interrupted = 0;
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			cleanup_and_exit(shell, lxr);
		}
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
		add_history(line);
		lexer(lxr, line);
		cmds = parser(lxr->tokens, shell);
		cmds = vars(cmds, shell);
		run_cmds(cmds, shell);
		free_loop(lxr, cmds, line);
	}
}

/*
	*clear_history, limpia el historial, para evitar leaks.
	*limpieza general antes de terminar.
	! Habrá que añadir limpiezas de own_env y comand_env
*/
void	clear_mini(t_lexer *lxr, t_mini *shell)
{
	rl_clear_history();
	ft_free_split(shell->env);
	free(lxr);
}

/*
	*main, cuya estructura básica sera:
	-inicializacion
	-mini
	-limpieza
*/
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
