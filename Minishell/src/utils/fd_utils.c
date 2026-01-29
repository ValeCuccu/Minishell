/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:11:40 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/21 15:11:41 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>

void	safe_close(int fd)
{
	int	ret;

	if (fd < 0)
		return ;
	while (1)
	{
		ret = close(fd);
		if (ret == 0)
			return ;
		if (errno == EINTR)
			continue ;
		return ;
	}
}
