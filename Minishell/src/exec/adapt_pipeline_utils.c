/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapt_pipeline_spawn.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2026/01/21 00:00:00 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <errno.h>
#include <unistd.h>

static int	ap_pipe_open_ctx(t_pipe_ctx *ctx)
{
	if (pipe(ctx->curr) < 0)
	{
		err_msg("pipe", strerror(errno));
		return (-1);
	}
	return (0);
}

static void	ap_child_setup_pipes_ctx(t_pipe_ctx *ctx)
{
	if (ctx->prev[0] != -1)
	{
		dup2(ctx->prev[0], STDIN_FILENO);
		safe_close(ctx->prev[0]);
		safe_close(ctx->prev[1]);
	}
	if (ctx->curr[1] != -1)
	{
		dup2(ctx->curr[1], STDOUT_FILENO);
		safe_close(ctx->curr[0]);
		safe_close(ctx->curr[1]);
	}
}

static void	ap_parent_close_pipes_ctx(t_pipe_ctx *ctx)
{
	if (ctx->i > 0)
	{
		safe_close(ctx->prev[0]);
		safe_close(ctx->prev[1]);
		ctx->prev[0] = -1;
		ctx->prev[1] = -1;
	}
	if (ctx->i < ctx->n - 1)
		safe_close(ctx->curr[1]);
}

static void	ap_child_free_and_exit(t_pipe_ctx *ctx, int ec)
{
	if (ctx->head)
		free_cmd_list(ctx->head);
	if (ctx->penv && *ctx->penv)
		free_env_list(*ctx->penv);
	if (ctx->pid_arr)
		free(ctx->pid_arr);
	_exit(ec);
}

int	ap_spawn_one(t_pipe_ctx *ctx)
{
	int	ec;

	ctx->curr[0] = -1;
	ctx->curr[1] = -1;
	if (ctx->i < ctx->n - 1 && ap_pipe_open_ctx(ctx) < 0)
		return (-1);
	ctx->pid_arr[ctx->i] = fork();
	if (ctx->pid_arr[ctx->i] < 0)
	{
		safe_close(ctx->curr[0]);
		safe_close(ctx->curr[1]);
		ctx->curr[0] = -1;
		ctx->curr[1] = -1;
		return (-1);
	}
	if (ctx->pid_arr[ctx->i] == 0)
	{
		ap_child_setup_pipes_ctx(ctx);
		ec = ap_run_child_exec(ctx->c, ctx->penv);
		ap_child_free_and_exit(ctx, ec);
	}
	ap_parent_close_pipes_ctx(ctx);
	return (0);
}
