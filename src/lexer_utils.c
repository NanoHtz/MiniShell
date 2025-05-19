/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:14:00 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/17 13:14:00 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

/*
* Archivo básico del lexer, el lector del input
* Lo primero es evaluar si estamos dentro o fuera de comillas simples o dobles
* Me he dado cuenta despues, asique sera lo siguiente.
* ft_escaped, evalua si el caracter esta escapado, precedido por un \, que anula el efecto especial del caracter
* Parece que \ no es necesario gestionarlo, luego esta funcion no es necesaria, la dejo por si acaso.
* ni gestionar ;
* operators, es la version mas sencilla, un simple debugeador.
*/
int	ft_escaped(const char *str, int i)
{
	int	count;

	count = 0;
	if (i < 0)
		return (0);
	while (str[i - 1 - count] == '\\' && (i - 1 - count) >=0)
		count++;
	return (count % 2);
}

void	operators(const char *str)
{
	int	i;
	int	dq;
	int	sq;

	i = 0;
	dq = 0;
	sq = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			dq = !dq;
			printf("Estamos en comillas dobles ? %d\n", dq);
		}
		if (str[i] == '\'')
		{
			sq = !sq;
			printf("Estamos en comillas simples ? %d\n", sq);
		}
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
				printf("El input tiene un operador lógico OR ||.\n");
			else
				printf("El input tiene un pipe |.\n");
		}
		else if (str[i] == '<')
		{
			if (str[i + 1] == '<')
			{
				printf("El input tiene un Heredoc.\n");
				i++;
			}
			else
				printf("El input tiene una entrada <.\n");
		}
		if (str[i] == '>')
		{
			if (str[i + 1] == '>')
			{
				printf("El input tiene una salida(append).\n");
				i++;
			}
			else
				printf("El input tiene una salida >(truncate).\n");
		}
		if (str[i] == '&')
		{
			if (str[i + 1] == '&')
			{
				printf("El input tiene un operador lógico AND &&.\n");
				i++;
			}
			else
				printf("El input tiene un background &.\n");
		}
		if (str[i] == '(')
		{
			printf("El input tiene una apertura de subshellagrupación (.\n");
		}
		if (str[i] == ')')
		{
			printf("El input tiene un cierre de subshellagrupación ).\n");
		}
		if (str[i] == '$')
		{
			if (str[i + 1] == '(')
				printf("El input tiene una llamada a una variable $.\n");
		}
		i++;
	}
}
