/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:59:35 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/21 12:05:44 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFFER_SIZE 1

static void	gnl_clear_stash(char **stash)
{
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
}

static char	*ft_extract_excess(char *line)
{
	ssize_t	i;
	char	*excess;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	excess = ft_substr(line, i + 1, ft_strlen(line) - (i + 1));
	if (!excess)
		return (NULL);
	line[i + 1] = '\0';
	return (excess);
}

static void	gnl_update_stash(char **stash, char *line)
{
	char	*new_stash;

	new_stash = ft_extract_excess(line);
	if (new_stash == NULL)
		*stash = NULL;
	else
		*stash = new_stash;
}

static char	*gnl_read_line(int fd, char **stash)
{
	char	*buffer;
	char	*line;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = ft_read_and_store(fd, stash, buffer);
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd == -1)
		return (gnl_clear_stash(&stash), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = gnl_read_line(fd, &stash);
	if (!line)
		return (NULL);
	gnl_update_stash(&stash, line);
	return (line);
}
