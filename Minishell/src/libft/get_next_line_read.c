/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_read.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:59:35 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/21 12:05:44 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFFER_SIZE 1

static int	gnl_has_nl(char *s)
{
	if (s && ft_strchr(s, '\n'))
		return (1);
	return (0);
}

static int	gnl_append_buffer(char **rest, char *buffer)
{
	char	*tmp;

	if (!*rest)
		*rest = ft_strdup("");
	if (!*rest)
		return (-1);
	tmp = *rest;
	*rest = ft_strjoin(tmp, buffer);
	free(tmp);
	if (!*rest)
		return (-1);
	return (0);
}

static int	gnl_read_step(int fd, char **rest, char *buffer, ssize_t *br)
{
	*br = read(fd, buffer, BUFFER_SIZE);
	if (*br == -1)
	{
		free(*rest);
		*rest = NULL;
		return (-1);
	}
	if (*br == 0)
		return (0);
	buffer[*br] = '\0';
	if (gnl_append_buffer(rest, buffer) < 0)
		return (-1);
	return (1);
}

char	*ft_read_and_store(int fd, char **rest, char *buffer)
{
	ssize_t	bt_read;
	int		step;

	if (gnl_has_nl(*rest))
		return (*rest);
	while (1)
	{
		step = gnl_read_step(fd, rest, buffer, &bt_read);
		if (step == -1)
			return (NULL);
		if (step == 0)
			break ;
		if (gnl_has_nl(*rest))
			break ;
	}
	return (*rest);
}
