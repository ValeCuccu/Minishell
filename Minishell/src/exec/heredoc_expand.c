/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:00:00 by anpastac          #+#    #+#             */
/*   Updated: 2026/01/22 19:58:06 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

int	hd_is_name_start(char c)
{
	return (ft_isalpha((unsigned char)c) || c == '_');
}

int	hd_is_name_char(char c)
{
	return (ft_isalnum((unsigned char)c) || c == '_');
}

char	*hd_join2(const char *a, const char *b)
{
	char	*res;
	size_t	la;
	size_t	lb;

	la = ft_strlen(a);
	lb = ft_strlen(b);
	res = (char *)malloc(la + lb + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, a, la);
	ft_memcpy(res + la, b, lb);
	res[la + lb] = '\0';
	return (res);
}

char	*hd_append_char(char *acc, char c)
{
	char	buf[2];
	char	*res;

	buf[0] = c;
	buf[1] = '\0';
	if (!acc)
		return (ft_strdup(buf));
	res = hd_join2(acc, buf);
	free(acc);
	return (res);
}

char	*hd_append_str(char *acc, const char *s)
{
	char	*res;

	if (!s)
		return (acc);
	if (!acc)
		return (ft_strdup(s));
	res = hd_join2(acc, s);
	free(acc);
	return (res);
}
