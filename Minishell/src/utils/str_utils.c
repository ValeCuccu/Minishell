/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2025/10/29 17:11:26 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

static size_t	ap_max_size(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ap_streq(const char *a, const char *b)
{
	size_t	la;
	size_t	lb;
	size_t	n;

	if (!a || !b)
		return (0);
	la = ft_strlen(a);
	lb = ft_strlen(b);
	n = ap_max_size(la, lb);
	n = n + 1;
	return (ft_strncmp(a, b, n) == 0);
}

int	ap_is_numeric_str(const char *s)
{
	int	i;
	int	has_digit;

	if (!s)
		return (0);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	has_digit = 0;
	while (s[i] && ft_isdigit((unsigned char)s[i]))
	{
		has_digit = 1;
		i++;
	}
	if (!has_digit)
		return (0);
	if (s[i] != '\0')
		return (0);
	return (1);
}

int	ap_is_valid_env_key(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (!(ft_isalpha((unsigned char)s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!(ft_isalnum((unsigned char)s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
