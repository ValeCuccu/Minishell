/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_close_extra_fds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:57:01 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/20 15:29:22 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

/*
** ms_close_extra_fds:
**   Chiude tutti i file descriptor >= 3.
**
**   - 0, 1, 2 (stdin, stdout, stderr) NON vengono toccati.
**   - Viene chiamata solo alla fine della minishell, prima di uscire.
**
**   Questo elimina i warning di Valgrind sui FD 3, 4 (e altri eventuali)
**   lasciati aperti da save_stdio / redir / ecc. a fine processo.
*/
void	ms_close_extra_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 256)
	{
		close(fd);
		fd++;
	}
}
