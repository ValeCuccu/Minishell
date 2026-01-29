/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:31:37 by vacuccu           #+#    #+#             */
/*   Updated: 2025/10/24 15:09:34 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

int	read_word_part(const char *s, int *i, char **acc)
{
	if (is_quote(s[*i]))
		return (read_single_quoted_part(s, i, acc));
	if (is_double_quote(s[*i]))
		return (read_double_quoted_part(s, i, acc));
	return (read_bare_part(s, i, acc));
}
