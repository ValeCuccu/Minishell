/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:28:39 by vacuccu           #+#    #+#             */
/*   Updated: 2025/01/17 14:36:20 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_num_len(int nb)
{
	size_t	len;

	len = 0;
	if (nb <= 0)
		len = 1;
	while (nb != 0)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

static char	*ft_build_str(char *str, long int n, size_t len)
{
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	else if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (n != 0)
	{
		str[len] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*str;

	len = ft_num_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	str = ft_build_str(str, n, len);
	return (str);
}

/*#include <stdio.h>
int main()
{
	int	nb = -2147483648;
	char *str = ft_itoa(nb);
	printf ("%s\n", str);
}*/