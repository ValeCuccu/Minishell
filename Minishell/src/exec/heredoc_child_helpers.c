/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:00:00 by anpastac          #+#    #+#             */
/*   Updated: 2026/01/23 08:52:11 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <unistd.h>

int	hd_child_open_in_or_exit(t_hd_ctx *ctx, int *fd_in)
{
	setup_signals_heredoc();
	ms_sig_clear();
	*fd_in = open_tty_in();
	if (*fd_in < 0)
	{
		hd_child_cleanup(ctx);
		_exit(1);
	}
	return (0);
}

int	hd_child_step(t_hd_ctx *ctx, int fd_in)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		ft_putstr_fd("> ", STDOUT_FILENO);
	if (ms_sig_get() == SIGINT)
		return (1);
	if (hd_next_line(fd_in, &line))
		return (1);
	if (hd_process_line(ctx, fd_in, line))
		return (1);
	return (0);
}

void	hd_child_finish(t_hd_ctx *ctx, int fd_in)
{
	if (ms_sig_get() == SIGINT)
		write(1, "\n", 1);
	close(ctx->fd);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	hd_child_cleanup(ctx);
	if (ms_sig_get() == SIGINT)
		_exit(130);
	_exit(0);
}
