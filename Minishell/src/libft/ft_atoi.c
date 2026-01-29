/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:59:58 by vacuccu           #+#    #+#             */
/*   Updated: 2025/01/14 12:46:14 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	rest;
	int	sign;

	i = 0;
	sign = 1;
	rest = 0;
	while (nptr[i] == ' ' || nptr[i] >= 9 && nptr[i] <= 13)
	{
		i++;
	}
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
		{
			sign = -1;
		}
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		rest = (rest * 10) + (nptr[i] - 48);
		i++;
	}
	return (rest * sign);
}
