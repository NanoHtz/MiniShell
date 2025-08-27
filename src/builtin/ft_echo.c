/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:00:28 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/15 20:00:28 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	* is_n: Hace la comprobacion de si tiene argumento n en cualquiera
	* de sus variantes -nnnnn -n etc
*/
int	is_n(char *av)
{
	int	i;

	i = 0;
	if (av[i] != '-')
		return (0);
	i++;
	if (av[i] != 'n')
		return (0);
	while (av[i] == 'n')
		i++;
	if (av[i] == '\0')
		return (1);
	return (0);
}

/*
	*echo_write: escribe 'len' bytes en stdout. En error, imprime el prefijo
	*"minishell: " en stderr y retorna 1. No hace perror (se reserva para "\n").
	*Retorno: 0 en éxito; 1 en error de write(2).
*/
static int	echo_write(const char *s, size_t len)
{
	if (write(1, s, len) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		return (1);
	}
	return (0);
}

/*
	*echo_newline: escribe un salto de línea en stdout. En error, imprime
	*"minishell: " y luego perror("write") para
	* replicar el comportamiento original.
	*Retorno: 0 en éxito; 1 en error de write(2).
*/
static int	echo_newline(void)
{
	if (write(1, "\n", 1) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("write");
		return (1);
	}
	return (0);
}

/*
	*consume_n_flags: avanza 'i' mientras existan
	* flags -n válidos y marca n_flag.
	*Retorno: (por referencia) i y n_flag actualizados.
*/
static void	consume_n_flags(t_cmd *cmd, int *i, int *n_flag)
{
	*n_flag = 0;
	while (cmd->av[*i] && is_n(cmd->av[*i]))
	{
		*n_flag = 1;
		(*i)++;
	}
}

/*
	*ft_echo: implementa el built-in echo con soporte para múltiples -n.
	*Semántica: imprime los argumentos separados por un espacio; si no hay -n,
	*termina con '\n'. Replica exactamente el manejo de errores de write(2):
	*para argumentos/espacios sólo imprime
	* "minishell: "; para '\n' además hace perror.
	*Retorno: 0 en éxito; 1 en error.
*/
int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;
	int	first;

	i = 1;
	consume_n_flags(cmd, &i, &n_flag);
	first = 1;
	while (cmd->av[i])
	{
		if (!first && echo_write(" ", 1))
			return (1);
		if (echo_write(cmd->av[i], ft_strlen(cmd->av[i])))
			return (1);
		first = 0;
		i++;
	}
	if (!n_flag && echo_newline())
		return (1);
	return (0);
}
