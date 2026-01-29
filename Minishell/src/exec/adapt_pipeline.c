/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapt_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2026/01/21 12:16:44 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <errno.h>
#include <sys/wait.h>

static int	ap_wait_all(pid_t *p, int n)
{
	int		i;
	int		st;
	int		last;
	pid_t	got;

	last = 0;
	i = 0;
	while (i < n)
	{
		while (1)
		{
			got = waitpid(p[i], &st, 0);
			if (got > 0)
				break ;
			if (got < 0 && errno == EINTR)
				continue ;
			break ;
		}
		if (got > 0)
			last = status_from_wait(st);
		i++;
	}
	return (last);
}

static void	ap_close_ctx_pipes(t_pipe_ctx *ctx)
{
	safe_close(ctx->prev[0]);
	safe_close(ctx->prev[1]);
	safe_close(ctx->curr[0]);
	safe_close(ctx->curr[1]);
	ctx->prev[0] = -1;
	ctx->prev[1] = -1;
	ctx->curr[0] = -1;
	ctx->curr[1] = -1;
}

static int	ap_pipeline_init(t_pipe_ctx *ctx, t_cmd *head, t_env **penv, int n)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * n);
	if (!pids)
		return (err_msg("malloc", "pids"), -1);
	ctx->i = 0;
	ctx->n = n;
	ctx->c = head;
	ctx->head = head;
	ctx->penv = penv;
	ctx->pid_arr = pids;
	ctx->prev[0] = -1;
	ctx->prev[1] = -1;
	ctx->curr[0] = -1;
	ctx->curr[1] = -1;
	return (0);
}

int	ap_run_pipeline(t_cmd *head, t_env **penv, int n)
{
	t_pipe_ctx	ctx;
	int			last_status;

	if (ap_pipeline_init(&ctx, head, penv, n) < 0)
		return (1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (ap_spawn_all(&ctx) < 0)
	{
		ap_close_ctx_pipes(&ctx);
		free(ctx.pid_arr);
		return (1);
	}
	last_status = ap_wait_all(ctx.pid_arr, n);
	if (isatty(STDIN_FILENO) && last_status == 130)
		write(1, "\n", 1);
	if (isatty(STDIN_FILENO) && last_status == 131)
		write(1, "Quit (core dumped)\n", 19);
	free(ctx.pid_arr);
	setup_signals_interactive();
	return (last_status);
}

int	ap_spawn_all(t_pipe_ctx *ctx)
{
	while (ctx->i < ctx->n)
	{
		if (ap_spawn_one(ctx) < 0)
			return (-1);
		if (ctx->i < ctx->n - 1)
		{
			ctx->prev[0] = ctx->curr[0];
			ctx->prev[1] = -1;
			ctx->curr[0] = -1;
		}
		ctx->c = ctx->c->next;
		ctx->i++;
	}
	return (0);
}
