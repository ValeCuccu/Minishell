/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:20:33 by vacuccu           #+#    #+#             */
/*   Updated: 2025/01/15 18:37:11 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	tft_strlen(char *str)
{
	size_t	l;

	l = 0;
	while (str[l] != '\0')
		l++;
	return (l);
}

static char	*tft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	ch = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == ch)
			return ((char *)(s + i));
		i++;
	}
	if (ch == '\0')
		return ((char *)(s + i));
	else
		return (NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && tft_strchr(set, s1[i]))
		i++;
	j = tft_strlen((char *)s1);
	while (j > i && tft_strchr(set, s1[j - 1]))
		j--;
	len = j - i;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	len = 0;
	while (i < j)
		str[len++] = s1[i++];
	str[len] = '\0';
	return (str);
}
