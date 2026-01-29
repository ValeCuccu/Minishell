/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 00:00:00 by vacuccu           #+#    #+#             */
/*   Updated: 2025/10/31 00:00:00 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <unistd.h>

static void	putnbr_fd_int(int n, int fd)
{
	char	buf[12];
	int		i;
	long	v;

	i = 11;
	v = n;
	buf[i--] = '\0';
	if (v == 0)
		buf[i--] = '0';
	if (v < 0)
		v = -v;
	while (v > 0)
	{
		buf[i--] = '0' + (v % 10);
		v /= 10;
	}
	if (n < 0)
		buf[i--] = '-';
	write(fd, &buf[i + 1], 11 - i);
}

void	dbg_dump_tokens(const char *tag, t_token *t)
{
	write(2, "[TOKENS:", 8);
	if (tag)
		write(2, tag, ft_strlen(tag));
	write(2, "]\n", 2);
	while (t)
	{
		write(2, tok_type_name(t->type), ft_strlen(tok_type_name(t->type)));
		write(2, "  <", 3);
		if (t->input)
			write(2, t->input, ft_strlen(t->input));
		write(2, ">  was_quoted=", 13);
		putnbr_fd_int(t->was_quoted, 2);
		write(2, "\n", 1);
		t = t->next;
	}
}
