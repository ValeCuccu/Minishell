/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:52:16 by vacuccu           #+#    #+#             */
/*   Updated: 2025/01/14 16:55:10 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	j;
	size_t	k;

	j = 0;
	if (little[0] == '\0')
		return ((char *)(big));
	while (j < len && big[j] != '\0')
	{
		k = 0;
		while (big[j + k] == little[k] && little[k] != '\0'
			&& (j + k) < len)
			k++;
		if (little[k] == '\0')
			return ((char *)(&big[j]));
		j++;
	}
	return (NULL);
}
