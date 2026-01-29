/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapt_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2026/01/21 11:59:58 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

static int	is_ms_heredoc_tmp(const char *path)
{
	size_t	i;

	if (!path)
		return (0);
	if (ft_strncmp(path, "/tmp/ms_hd_", 11) != 0)
		return (0);
	i = 11;
	if (path[i] == '\0')
		return (0);
	while (path[i] >= '0' && path[i] <= '9')
		i++;
	if (ft_strncmp(path + i, ".tmp", 5) != 0)
		return (0);
	return (1);
}

int	ap_open_for_redir(t_redir *r)
{
	int	fd;

	fd = -1;
	if (r->type == REDIR_IN)
		fd = open(r->filename, O_RDONLY);
	else if (r->type == REDIR_OUT)
		fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (r->type == REDIR_APPEND)
		fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	return (fd);
}

static int	ap_dup_target(int fd, int target)
{
	if (dup2(fd, target) < 0)
	{
		close(fd);
		return (err_msg("dup2", strerror(errno)), -1);
	}
	return (0);
}

static int	ap_maybe_unlink_heredoc(int fd, t_redir *r)
{
	if (r->type == REDIR_IN && is_ms_heredoc_tmp(r->filename))
	{
		if (unlink(r->filename) < 0)
		{
			close(fd);
			return (err_msg("unlink", strerror(errno)), -1);
		}
	}
	return (0);
}

int	ap_apply_one_redir(t_redir *r)
{
	int	fd;

	fd = ap_open_for_redir(r);
	if (fd < 0)
		return (err_msg(r->filename, strerror(errno)), -1);
	if (ap_maybe_unlink_heredoc(fd, r) < 0)
		return (-1);
	if (r->type == REDIR_IN)
	{
		if (ap_dup_target(fd, STDIN_FILENO) < 0)
			return (-1);
	}
	else if (ap_dup_target(fd, STDOUT_FILENO) < 0)
		return (-1);
	close(fd);
	return (0);
}
