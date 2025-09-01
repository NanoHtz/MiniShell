/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:41:38 by pablo             #+#    #+#             */
/*   Updated: 2025/09/01 09:13:33 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

static char	*expand_hd_if_needed(t_hdoc_ctx *ctx, const char *line)
{
	if (ctx->r->exp == 0)
		return (expand_line_heredoc(line, ctx->cmd_env, ctx->shell));
	return ((char *)line);
}

int	hdoc_loop_iter(char **line, size_t *len, int pipefd[2], t_hdoc_ctx *ctx)
{
	ssize_t	n;
	char	*out;

	if (write(2, "> ", 2) < 0)
		return (handle_write_error(*line, pipefd));
	n = getline(line, len, stdin);
	if (n < 0)
		return (heredoc_eof_handler(ctx->r->target, *line, pipefd));
	if (n > 0 && (*line)[n - 1] == '\n')
		(*line)[n - 1] = '\0';
	if (ft_strcmp(*line, ctx->r->target) == 0)
		return (heredoc_delim_found(pipefd));
	out = expand_hd_if_needed(ctx, *line);
	if (!out)
		return (handle_write_error(*line, pipefd));
	if (write(pipefd[1], out, ft_strlen(out)) < 0
		|| write(pipefd[1], "\n", 1) < 0)
		return (handle_write_error(out, pipefd));
	if (out != *line)
		free(out);
	return (1);
}

int	handler_heredoc(t_redir *r, char **cmd_env, t_mini *shell)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipefd[0]);
		run_heredoc_loop(r, pipefd[1], cmd_env, shell);
		exit(0);
	}
	else
	{
		if (wait_heredoc(pipefd, pid, shell) < 0)
			return (-1);
		return (pipefd[0]);
	}
}

void	run_heredoc_loop(t_redir *r, int write_fd, char **env, t_mini *shell)
{
	char		*line;
	size_t		len;
	int			pipefd[2];
	int			res;
	t_hdoc_ctx	ctx;

	ctx.r = r;
	ctx.cmd_env = env;
	ctx.shell = shell;
	line = NULL;
	len = 0;
	pipefd[1] = write_fd;
	while (1)
	{
		res = hdoc_loop_iter(&line, &len, pipefd, &ctx);
		if (res != 1)
			break ;
	}
	free(line);
	close(write_fd);
}
