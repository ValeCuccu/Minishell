/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 00:00:00 by antonio           #+#    #+#             */
/*   Updated: 2026/01/21 15:11:23 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <unistd.h>
#include <errno.h>

int	ap_err_msg(const char *where, const char *msg)
{
	write(2, "minishell: ", 11);
	if (where && where[0])
	{
		write(2, where, ft_strlen(where));
		if (msg && msg[0])
			write(2, ": ", 2);
	}
	if (msg && msg[0])
		write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (-1);
}

int	ap_err_msg_quoted(const char *where, const char *arg, const char *msg)
{
	write(2, "minishell: ", 11);
	if (where && where[0])
	{
		write(2, where, ft_strlen(where));
		write(2, ": ", 2);
	}
	write(2, "'", 1);
	if (arg && arg[0])
		write(2, arg, ft_strlen(arg));
	write(2, "': ", 3);
	if (msg && msg[0])
		write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (-1);
}

void	ap_fatal_perror(const char *where)
{
	write(2, "minishell: ", 11);
	if (where && where[0])
	{
		write(2, where, ft_strlen(where));
		write(2, ": ", 2);
	}
	if (errno)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
	}
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	err_msg(const char *a, const char *b)
{
	if (errno == 0 || errno == EINTR)
		return ;
	ap_err_msg(a, b);
}

void	err_msg_quoted(const char *where, const char *arg, const char *msg)
{
	ap_err_msg_quoted(where, arg, msg);
}
