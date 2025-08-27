/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:19:28 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/07/21 19:19:28 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	redir_read(t_redir *r)
{
	int	fd;

	fd = open(r->target, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(r->target);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redir_write(t_redir *r)
{
	int	fd;

	fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(r->target);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redir_append(t_redir *r)
{
	int	fd;

	fd = open(r->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(r->target);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redir_heredoc(t_redir *r, t_cmd *cmd, t_mini *shell)
{
	int	fd;

	fd = handler_heredoc(r, cmd->cmd_env, shell);
	if (fd < 0)
		return (-1);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
// Meter el type arrastrandolo por el código.

int	handle_redirections(t_cmd *cmd)
{
	t_redir		*r;
	int			ret;

	if (!cmd)
		return(0); // Hacer una comprobacion de redireccion.
	r = cmd->redirs;
	while (r)
	{
		if (r->type == T_RIN)
			ret = redir_read(r);
		else if (r->type == T_ROUT)
			ret = redir_write(r);
		else if (r->type == T_RAPPEND)
			ret = redir_append(r);
		else if (r->type == T_RHEREDOC)
		{
			if (g_interrupted)
				return (-1);
			if (dup2(r->fd, STDIN_FILENO) < 0)
			{
				ft_putstr_fd("minishell: ", 2);
				perror("dup2");
				close(r->fd);
				return (-1);
			}
			close(r->fd);
			ret = 0;
		}
		else
			ret = 0;
		if (ret < 0)
			return (-1);
		r = r->next;
	}
	return (0);
}
