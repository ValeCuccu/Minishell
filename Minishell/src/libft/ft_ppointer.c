/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ppointer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:24:34 by vacuccu           #+#    #+#             */
/*   Updated: 2025/05/05 08:41:48 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ppointer(unsigned long *ptr)
{
	unsigned long	addr;
	int				printed_chars;

	printed_chars = 0;
	if (ptr == NULL)
	{
		printed_chars += ft_pstr("(nil)");
		return (5);
	}
	else
	{
		addr = (unsigned long)ptr;
		printed_chars += ft_pstr("0x");
		printed_chars += ft_pnbr_base(addr, "0123456789abcdef");
	}
	return (printed_chars);
}

/* int main(void)
{
    int a = 42;
    int ptr_a = &a;
    int null_ptr = NULL;
	int null_ptr2 = NULL;

    // Test 1: Puntatore valido
    printf("Test 1: Puntatore valido\n");
    printf("Expected: %p\n", (void *)ptr_a);
    ft_printf("Output:   ");
    ft_ppointer(ptr_a);
    printf("\n\n");

    // Test 2: Puntatore nullo
    printf("Test 2: Puntatore nullo\n");
    printf("Expected: (nil)\n");
    ft_printf("Output:   ");
    ft_ppointer(null_ptr);
    printf("\n\n");

    // Test 3: Puntatore a una stringa
    printf("Test 3: Puntatore a una stringa\n");
    char str[] = "Hello, world!";
    printf("Expected: %p\n", (void *)str);
    ft_printf("Output:   ");
    ft_ppointer(str);
    printf("\n\n");

    // Test 4: Puntatore a una funzione
    printf("Test 4: Puntatore a una funzione\n");
    printf("Expected: %p\n", (void *)ft_ppointer);
    ft_printf("Output:   ");
    ft_ppointer((void *)ft_ppointer);
    printf("\n\n");

    // Test 4: Puntatori nulli
    printf("Test 4: Puntatori nulli \n");
    printf("Expected: (nil) (nil)");
    ft_printf("Output:   ");
    ft_ppointer(null_ptr);
	ft_ppointer(null_ptr2);
    printf("\n\n");

    return 0;
} */