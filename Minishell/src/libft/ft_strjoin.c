/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:59:22 by vacuccu           #+#    #+#             */
/*   Updated: 2025/01/14 18:04:46 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*tft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
	{
		i++;
	}
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			tot;
	char			*n_str;

	tot = ((ft_strlen(s1)) + (ft_strlen(s2)));
	n_str = (char *)malloc((tot + 1) * sizeof(char));
	if (!n_str)
		return (NULL);
	n_str[0] = '\0';
	tft_strcat(n_str, s1);
	tft_strcat(n_str, s2);
	return (n_str);
}
