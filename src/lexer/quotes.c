/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:35:17 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/20 11:35:17 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*copy_value:
	* Copia el valor de la cadena entrecomillada.
*/
int	copy_value(int len, int start, t_lexer *lxr)
{
	char	*value;

	value = malloc(len + 1);
	if (!value)
		return (-1);
	ft_memcpy(value, lxr->input + start, len);
	value[len] = '\0';
	token(lxr, T_QUOTE, value, 0);
	free(value);
	return (0);
}

/*
	*quotes:
	* Asigna a una variable si las comillas son " o '.
	* Recorre la cadena hasta encontrar el mismo tipo de comillas.
	* Copia desde start la longitud len.
	* Si existe una comilla de cierre la salta.
	! -> No tengo claro como tokenizar comillas que no tengan cierre
	! -> Como palabra o como quote.
*/
int	quotes(t_lexer *lxr)
{
	char	quote;
	int		start;
	int		len;

	quote = lxr->input[lxr->pos];
	if (quote != '"' && quote != '\'')
		return (0);
	start = ++lxr->pos;
	while (lxr->input[lxr->pos] != '\0' && lxr->input[lxr->pos] != quote)
		lxr->pos++;
	len = lxr->pos - start;
	if (copy_value(len, start, lxr) < 0)
		return (-1);
	if (lxr->input[lxr->pos] == quote)
		lxr->pos++;
	return (1);
}
