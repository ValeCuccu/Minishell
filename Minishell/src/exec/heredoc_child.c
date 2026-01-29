/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2026/01/29 13:09:31 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

void	hd_child_cleanup(t_hd_ctx *ctx)
{
	get_next_line(-1);
	clear_history();
	if (ctx && ctx->st)
	{
		if (ctx->st->head)
			free_cmd_list(ctx->st->head);
		if (ctx->st->env)
			free_env_list(ctx->st->env);
	}
}

int	open_tty_in(void)
{
	int	fd;

	if (!isatty(STDIN_FILENO))
		return (STDIN_FILENO);
	fd = open("/dev/tty", O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	hd_next_line(int fd_in, char **line)
{
	*line = get_next_line(fd_in);
	if (!*line && ms_sig_get() == SIGINT)
		return (1);
	if (ms_sig_get() == SIGINT)
	{
		if (*line)
			free(*line);
		*line = NULL;
		return (1);
	}
	if (!*line)
		return (1);
	return (0);
}

int	hd_process_line(t_hd_ctx *ctx, int fd_in, char *line)
{
	size_t	len;
	char	*exp;

	len = ft_strlen(line);
	if (len && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (ft_strncmp(line, ctx->delim, ft_strlen(ctx->delim) + 1) == 0)
		return (free(line), 1);
	if (!ctx->expand)
		return (ft_putendl_fd(line, ctx->fd), free(line), 0);
	exp = hd_expand_vars(line, ctx->st->env);
	free(line);
	if (!exp)
	{
		close(ctx->fd);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		hd_child_cleanup(ctx);
		_exit(1);
	}
	ft_putendl_fd(exp, ctx->fd);
	free(exp);
	return (0);
}

void	heredoc_child(t_hd_ctx *ctx)
{
	int	fd_in;

	hd_child_open_in_or_exit(ctx, &fd_in);
	while (1)
	{
		if (hd_child_step(ctx, fd_in))
			break ;
	}
	hd_child_finish(ctx, fd_in);
}
