/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:45:00 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/22 09:53:00 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

/* valida formato [-|+]?[0-9]+ e calcola (signed) mod 256 in un colpo solo */
static int	ms_parse_digits_mod256(const char *s, size_t i,
				unsigned int *m_out)
{
	unsigned int	m;

	m = 0;
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		m = (m * 10u + (unsigned int)(s[i] - '0')) & 0xFFu;
		i++;
	}
	*m_out = m;
	return (1);
}

int	ms_parse_exit_mod256(const char *s, int *ok)
{
	size_t			i;
	int				sign;
	unsigned int	m;

	*ok = 0;
	if (!s || !*s)
		return (0);
	i = 0;
	sign = 1;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (!s[i] || !ms_parse_digits_mod256(s, i, &m))
		return (0);
	*ok = 1;
	if (sign < 0)
		m = ((unsigned int)(-(int)m)) & 0xFFu;
	return ((int)m);
}

/* wrapper comodo: ritorna 1 se valido e riempie *out con il codice 0..255 */
int	ms_try_parse_exit(const char *s, int *out)
{
	int	ok;
	int	code;

	code = ms_parse_exit_mod256(s, &ok);
	if (!ok)
		return (0);
	*out = code;
	return (1);
}
