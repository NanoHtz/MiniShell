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
	*unclosed_quote: emite un token de error por comilla sin cerrar.
	*dado el tipo de comilla que abrió el bloque, añade
	*un T_ERROR con el literal correspondiente y devuelve 1 para indicar
	*que la situación ya se ha gestionado por completo.
*/
int	unclosed_quote(t_lexer *lxr, char quote)
{
	if (quote == '\'')
		token(lxr, T_ERROR, "'", 0);
	else
		token(lxr, T_ERROR, "\"", 0);
	return (1);
}

/*
	*copy_value: copia un segmento de la entrada y crea el token de comillas.
	*Qué hace:
	*1) Reserva (len + 1) bytes,lxr->input[start .. start+len) y cierra con '\0'.
	*2) Emite T_SQUOTE si s_q==1; en caso contrario emite T_QUOTE.
	*3) Libera el buffer temporal tras llamar a token().
	*Retorno: 0 en éxito; -1 si malloc falla.
	*Efectos: añade un token a lxr->tokens. No altera lxr->pos.
*/
int	copy_value(int len, int start, t_lexer *lxr, int s_q)
{
	char	*value;

	value = malloc(len + 1);
	if (!value)
		return (-1);
	ft_memcpy(value, lxr->input + start, len);
	value[len] = '\0';
	if (s_q == 1)
		token(lxr, T_SQUOTE, value, 0);
	else
		token(lxr, T_QUOTE, value, 0);
	free(value);
	return (0);
}

/*
	*quotes: gestiona las comillas
	*Guarda el tipo de comilla que abre, y marca una flag si es simple
	*2) Avanza para fijar el inicio y busca la comilla de cierre.
	*3) Si no hay cierre antes de '\0', delega en unclosed_quote() y retorna 1.
	*4) Calcula la longitud y delega en copy_value() para construir el token.
	*5) Si encuentra la comilla de cierre, avanza pos tras ella.
	*Retorna: 1 si trató comillas (éxito o error), 0 si no había comillas,
	*         -1 si copy_value falla.
*/
int	quotes(t_lexer *lxr)
{
	char	quote;
	int		start;
	int		len;
	int		s_q;

	s_q = 0;
	quote = lxr->input[lxr->pos];
	if (quote != '"' && quote != '\'')
		return (0);
	if (quote == '\'')
		s_q = 1;
	start = ++lxr->pos;
	while (lxr->input[lxr->pos] != '\0' && lxr->input[lxr->pos] != quote)
		lxr->pos++;
	if (lxr->input[lxr->pos] == '\0')
		return (unclosed_quote(lxr, quote));
	len = lxr->pos - start;
	if (copy_value(len, start, lxr, s_q) < 0)
		return (-1);
	if (lxr->input[lxr->pos] == quote)
		lxr->pos++;
	return (1);
}
