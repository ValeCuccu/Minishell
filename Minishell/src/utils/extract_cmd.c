/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:07:15 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/20 15:30:27 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

char	*substr_dup(const char *src, int start, int end)
{
	int		len;
	char	*dest;

	if (end < start)
		end = start;
	len = end - start;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, src + start, len);
	dest[len] = '\0';
	return (dest);
}

char	*join_and_free(char *s1, char *s2)
{
	size_t	l1;
	size_t	l2;
	char	*dest;

	if (!s1)
		return (ft_strdup(s2));
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	dest = (char *)malloc(l1 + l2 + 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1, l1);
	ft_memcpy(dest + l1, s2, l2);
	dest[l1 + l2] = '\0';
	free(s1);
	return (dest);
}

int	append_segment(char **dest, const char *src, int start, int end)
{
	char	*seg;
	char	*tmp;

	seg = substr_dup(src, start, end);
	if (!seg)
		return (0);
	tmp = join_and_free(*dest, seg);
	free(seg);
	if (!tmp)
		return (0);
	*dest = tmp;
	return (1);
}
