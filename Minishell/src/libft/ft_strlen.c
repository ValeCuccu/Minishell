/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:12:48 by vacuccu           #+#    #+#             */
/*   Updated: 2025/01/14 12:42:56 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}
/*
#include <stdio.h>
int main()
{
    const char *str = "Hello, World!";
    
    // Utilizziamo la nostra funzione per calcolare la lunghezza
    //size_t len = ft_strlen(str);
    
    printf("%zu\n", ft_strlen(str));
    
    return 0;
}*/
