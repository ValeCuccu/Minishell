/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonio <student.42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2025/10/28 00:00:00 by antonio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

/*
** ap_is_n_flag:
**   Ritorna 1 se la stringa è una flag tipo:
**     -n
**     -nnn
**     -nnnnnnnn
**   Altrimenti 0.
**
**   echo -n   -> niente newline
**   echo -nnn -> ancora niente newline
*/
static int	ap_is_n_flag(const char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	i = 2;
	while (s[i] == 'n')
		i++;
	if (s[i] != '\0')
		return (0);
	return (1);
}

/*
** bi_echo:
**
** Comportamento:
**   echo [ -n ... ] [arg ...]
**
** - Se trova una o più flag -n / -nnn ... all'inizio,
**   NON stampa il newline finale.
**
** - Poi stampa tutti gli argomenti rimanenti separati da spazio.
**
** Return:
**   0 sempre (echo di norma non fallisce).
*/
int	bi_echo(char **av)
{
	int	i;
	int	print_nl;

	i = 1;
	print_nl = 1;
	while (av[i] && ap_is_n_flag(av[i]))
	{
		print_nl = 0;
		i++;
	}
	while (av[i])
	{
		ft_putstr_fd(av[i], 1);
		if (av[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (print_nl)
		ft_putstr_fd("\n", 1);
	return (0);
}
