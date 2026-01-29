/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2026/01/23 08:57:37 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>

static char	*next_heredoc_path(t_ms_state *st)
{
	char	*num;
	char	*tmp;
	char	*res;

	if (!st)
		return (NULL);
	num = ft_itoa(st->hd_idx++);
	if (!num)
		return (NULL);
	tmp = ft_strjoin("/tmp/ms_hd_", num);
	free(num);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, ".tmp");
	free(tmp);
	return (res);
}

static int	run_heredoc_process(t_hd_ctx *ctx)
{
	pid_t	pid;
	int		st;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (setup_signals_interactive(), -1);
	if (pid == 0)
	{
		free(ctx->path);
		ctx->path = NULL;
		heredoc_child(ctx);
	}
	if (waitpid(pid, &st, 0) < 0)
		return (setup_signals_interactive(), -1);
	setup_signals_interactive();
	if (WIFEXITED(st) && WEXITSTATUS(st) == 130)
		return (errno = EINTR, -1);
	if (WIFSIGNALED(st) && WTERMSIG(st) == SIGINT)
		return (errno = EINTR, -1);
	if (WIFEXITED(st) && WEXITSTATUS(st) != 0)
		return (-1);
	return (0);
}

static int	hd_ctx_open_tmp(t_hd_ctx *ctx, t_redir *r, t_ms_state *st)
{
	ft_bzero(ctx, sizeof(*ctx));
	ctx->delim = r->filename;
	ctx->expand = r->expand;
	ctx->st = st;
	ctx->path = next_heredoc_path(st);
	if (!ctx->path)
		return (-1);
	ctx->fd = open(ctx->path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (ctx->fd < 0)
		return (free(ctx->path), -1);
	return (0);
}

static int	hd_fail_cleanup(t_hd_ctx *ctx)
{
	close(ctx->fd);
	unlink(ctx->path);
	free(ctx->path);
	return (-1);
}

int	heredoc_run(t_redir *r, char **out_path, t_ms_state *st)
{
	t_hd_ctx	ctx;

	if (out_path)
		*out_path = NULL;
	if (!r || !r->filename || !st)
		return (-1);
	if (hd_ctx_open_tmp(&ctx, r, st) < 0)
		return (-1);
	if (run_heredoc_process(&ctx) < 0)
		return (hd_fail_cleanup(&ctx));
	close(ctx.fd);
	if (out_path)
		*out_path = ctx.path;
	else
		free(ctx.path);
	return (0);
}
