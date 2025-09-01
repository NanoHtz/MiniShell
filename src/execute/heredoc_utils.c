/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:21:09 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/07/21 19:21:09 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	wait_heredoc(int *pipefd, pid_t pid, t_mini *shell)
{
	int		status;

	signal(SIGINT, SIG_IGN);
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipefd[0]);
		g_interrupted = 1;
		shell->last_status = 130;
		return (-1);
	}
	return (0);
}

int	handle_write_error(char *line, int pipefd[2])
{
	free(line);
	close(pipefd[0]);
	close(pipefd[1]);
	return (-1);
}

void	warn_delimiter_eof(const char *delimiter)
{
	write(2, "minishell: warning: delimited by eof", 36);
	write(2, delimiter, ft_strlen(delimiter));
	write(2, "`)\n", 3);
}

int	heredoc_eof_handler(const char *delimiter, char *line, int pipefd[2])
{
	warn_delimiter_eof(delimiter);
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}

int	heredoc_delim_found(int pipefd[2])
{
	close(pipefd[1]);
	return (pipefd[0]);
}
