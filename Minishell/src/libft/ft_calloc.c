/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:57:21 by vacuccu           #+#    #+#             */
/*   Updated: 2025/01/17 15:18:54 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	tft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	tot;
	char	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	tot = (nmemb * size);
	ptr = (void *)malloc(tot);
	if (ptr == NULL)
		return (NULL);
	tft_bzero(ptr, tot);
	return (ptr);
}
