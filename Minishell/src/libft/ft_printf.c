/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:50:55 by vacuccu           #+#    #+#             */
/*   Updated: 2025/05/05 08:42:21 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*format_management(char format, va_list args, int *len)
{
	if (format == 'c')
		*len += (ft_pchar(va_arg(args, int)));
	else if (format == 's')
		*len += (ft_pstr(va_arg(args, char *)));
	else if (format == 'd' || format == 'i')
		*len += (ft_pnbr(va_arg(args, int)));
	else if (format == 'u')
		*len += (ft_pnbr_unsigned(va_arg(args, unsigned int)));
	else if (format == 'x')
	{
		*len += ft_pnbr_base(va_arg(args, unsigned int), "0123456789abcdef");
	}
	else if (format == 'X')
	{
		*len += ft_pnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF");
	}
	else if (format == 'p')
		*len += ft_ppointer(va_arg(args, unsigned long *));
	else if (format == '%')
	{
		*len += ft_pstr("%");
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			format_management(format[i + 1], args, &len);
			i++;
		}
		else
			len += ft_pchar(format[i]);
		i++;
	}
	va_end(args);
	return (len);
}

/* int main ()
{
	uintptr_t *ptr1 = NULL;
	uintptr_t *ptr2 = NULL;
	printf ("%p %p\n\n", ptr1, ptr2);
	ft_printf ("%p %p", ptr1, ptr2);
	return (0);
} */
