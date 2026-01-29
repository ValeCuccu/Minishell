/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:45:00 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/21 15:09:29 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

/* stampa a+b+c su stderr, poi '\n' */
void	ms_puterr3(const char *a, const char *b, const char *c)
{
	if (a)
		ft_putstr_fd((char *)a, 2);
	if (b)
		ft_putstr_fd((char *)b, 2);
	if (c)
		ft_putstr_fd((char *)c, 2);
	ft_putstr_fd("\n", 2);
}

/* [-|+]?[0-9]+ */
int	ms_is_numeric(const char *s)
{
	size_t	i;

	if (!s || !*s)
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

/* atoll semplice: chiamare solo dopo ms_is_numeric */
long long	ms_atoll(const char *s)
{
	long long	v;
	int			sign;
	size_t		i;

	sign = 1;
	v = 0;
	i = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] && ft_isdigit((unsigned char)s[i]))
	{
		v = v * 10 + (s[i] - '0');
		i++;
	}
	return (v * sign);
}

/* normalizza in [0..255] come bash */
int	ms_norm_code(long long v)
{
	unsigned long long	u;

	u = (unsigned long long)v;
	return ((int)(u & 0xFFu));
}

/* calcola (signed) modulo 256 senza overflow: [-|+]?[0-9]+ */
int	ms_mod256_str(const char *s)
{
	size_t			i;
	int				sign;
	unsigned int	m;

	if (!s || !*s)
		return (0);
	i = 0;
	sign = 1;
	m = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (!s[i])
		return (0);
	while (s[i] && ft_isdigit((unsigned char)s[i]))
	{
		m = (m * 10u + (unsigned int)(s[i] - '0')) & 0xFFu;
		i++;
	}
	if (sign < 0)
		m = ((unsigned int)(-(int)m)) & 0xFFu;
	return ((int)m);
}
