/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:38:30 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/05/28 13:38:30 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	* is_delimiter:
	* Comprueba si el cracter es un espacio o un caracter especial.
*/
int	is_delimiter(char c)
{
	return (ft_isspace((unsigned char)c) || ft_strchr("<>|\"'", c) != NULL);
}

/*
	* take_two:
	* Comprueba si el caracter actual y el siguiente son el mismo.
	* Para casos como >>
*/
int	take_two(const char *line, int i, const char op)
{
	if (line[i] == op && line[i + 1] == op)
		return (1);
	return (0);
}
