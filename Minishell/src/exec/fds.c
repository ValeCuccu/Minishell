/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2025/12/05 16:06:09 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <errno.h>

/*
** Salva gli fd correnti di STDIN e STDOUT in sv[0] e sv[1].
** Ritorna 0 se ok, -1 se errore.
*/
int	save_stdio(int sv[2])
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	if (fd_in < 0)
	{
		err_msg("dup", strerror(errno));
		sv[0] = -1;
		sv[1] = -1;
		return (-1);
	}
	fd_out = dup(STDOUT_FILENO);
	if (fd_out < 0)
	{
		err_msg("dup", strerror(errno));
		close(fd_in);
		sv[0] = -1;
		sv[1] = -1;
		return (-1);
	}
	sv[0] = fd_in;
	sv[1] = fd_out;
	return (0);
}

/*
** Ripristina STDIN/STDOUT originali usando sv[]
** e poi chiude le copie salvate.
** Ritorna 0 se ok, -1 se errore.
*/
int	restore_stdio(int sv[2])
{
	int	err;

	err = 0;
	if (sv[0] >= 0)
	{
		if (dup2(sv[0], STDIN_FILENO) < 0)
		{
			err_msg("dup2", strerror(errno));
			err = -1;
		}
		close(sv[0]);
		sv[0] = -1;
	}
	if (sv[1] >= 0)
	{
		if (dup2(sv[1], STDOUT_FILENO) < 0)
		{
			err_msg("dup2", strerror(errno));
			err = -1;
		}
		close(sv[1]);
		sv[1] = -1;
	}
	return (err);
}
