/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:04:25 by vacuccu           #+#    #+#             */
/*   Updated: 2025/01/14 12:44:54 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		p[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
/*
int main ()
{
	int c = 'a';
	size_t n = 5;
	char *s = (char *)malloc (sizeof(char) * (n + 1));
	s = ft_memset(s, c, n);
	printf ("%s\n", s);
	free (s);
	return (0);
}
*/
