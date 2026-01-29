/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:54:51 by vacuccu           #+#    #+#             */
/*   Updated: 2025/01/14 12:43:56 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lend;
	size_t	lens;
	size_t	i;

	lend = 0;
	lens = 0;
	i = 0;
	while (dst[lend] != '\0' && lend < size)
		lend++;
	while (src[lens] != '\0')
		lens++;
	if (lend == size)
		return (size + lens);
	while (src[i] != '\0' && lend + i < size - 1)
	{
		dst[lend + i] = src[i];
		i++;
	}
	if (lend + i < size)
		dst[lend + i] = '\0';
	return (lend + lens);
}
/*#include <stdio.h>
int main()
{
	char dest[10] = "Hello";
	char *src = "World";
	printf("%zu\n", ft_strlcat(dest, src, 11));
	ft_strlcat(dest, src, 10);
	printf("\n%s", dest);
	return (0);
}*/
