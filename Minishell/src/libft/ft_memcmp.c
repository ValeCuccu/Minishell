/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:45:12 by vacuccu           #+#    #+#             */
/*   Updated: 2025/01/14 17:16:05 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*uc1;
	unsigned char	*uc2;
	size_t			i;

	uc1 = (unsigned char *) s1;
	uc2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (uc1[i] != uc2[i])
			return ((uc1[i] - uc2[i]));
		i++;
	}
	return (0);
}
