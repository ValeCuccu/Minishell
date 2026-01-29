/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:54:26 by vacuccu           #+#    #+#             */
/*   Updated: 2025/01/14 12:43:27 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (c - 32);
	}
	return (c);
}
/*
#include <unistd.h>
int	main (int argc, char **argv)
{
	int i;

	i = 0;
	
	if (argc == 2)
	{
		
		while (argv[1][i] != '\0')
		{
			argv[1][i] = ft_toupper(argv[1][i]);
			write (1, &argv[1][i], 1);
			i++;
		}
		
	}
	return (0);
}
*/
