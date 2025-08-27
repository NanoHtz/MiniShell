/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:27:07 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/15 18:27:07 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	syntax_error(t_mini *sh, const char *tok)
{
	const char	*shown;

	if (!tok || !*tok)
		tok = "newline";
	if (tok[0] == '\'' && tok[1] == '\0')
		return (syntax_error_unclosed_quote(sh, '\''));
	if (tok[0] == '\"' && tok[1] == '\0')
		return (syntax_error_unclosed_quote(sh, '\"'));
	shown = tok;
	if (tok[0] == '<' && tok[1] == '<' && tok[2] == '<' && tok[3] == '\0')
		shown = "newline";
	else if (tok[0] == '>' && tok[1] == '>' && tok[2] == '>' && tok[3] == '\0')
		shown = ">";
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(shown, 2);
	ft_putstr_fd("'\n", 2);
	sh->last_status = 2;
	return (-1);
}

int	syntax_error_unclosed_quote(t_mini *sh, char quote)
{
	ft_putstr_fd("minishell: unexpected EOF while looking ", 2);
	ft_putstr_fd("for matching `", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("'\n", 2);
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	sh->last_status = 2;
	return (-1);
}
