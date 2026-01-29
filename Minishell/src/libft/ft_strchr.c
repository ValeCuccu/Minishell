/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:51:08 by vacuccu           #+#    #+#             */
/*   Updated: 2025/01/13 17:25:17 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			ch;

	ch = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == ch)
		return ((char *) &s[i]);
	return (NULL);
}

/*int main()
{
    const char *s = "Hello World";
    char c = 'o';
    char *result = ft_strchr(s, c);

    if (result)
        printf("Il carattere '%c' è stato trovato: %s\n", c, result);
    else
        printf("Il carattere '%c' non è stato trovato.\n", c);

    return (0);
}*/
