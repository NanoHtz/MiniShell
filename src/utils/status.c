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

void	handle_command_not_found(t_cmd *cmd, char **exec_env)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->av[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_charpp(exec_env);
	_exit(127);
}

void	handle_directory_error(t_cmd *cmd, char **exec_env)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->av[0], 2);
	ft_putendl_fd(": Is a directory", 2);
	free_charpp(exec_env);
	_exit(126);
}

void	handle_execve_error(char *cmd_name, char **exec_env)
{
	int	err;

	err = errno;
	perror(cmd_name);
	free_charpp(exec_env);
	if (err == EACCES || err == EPERM)
		_exit(126);
	if (err == ENOENT)
		_exit(127);
	_exit(127);
}
