/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:04:11 by vacuccu           #+#    #+#             */
/*   Updated: 2025/12/09 16:24:08 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

/* SINGLE QUOTE: copia tutto tra ' ... ' (nessuna espansione) */
int	read_single_quoted_part(const char *s, int *i, char **acc)
{
	int	j;

	if (s[*i] != '\'')
		return (0);
	j = *i + 1;
	while (s[j] && s[j] != '\'')
		j++;
	if (s[j] != '\'')
		return (printf("syntax error: unclosed single quote\n"), 0);
	if (!append_segment(acc, s, *i, j + 1))
		return (0);
	*i = j + 1;
	return (1);
}

/* DOUBLE QUOTE: copia tutto tra "..." (expansion in fase successiva) */
int	read_double_quoted_part(const char *s, int *i, char **acc)
{
	int	j;

	if (s[*i] != '"')
		return (0);
	j = *i + 1;
	while (s[j] && s[j] != '"')
		j++;
	if (s[j] != '"')
		return (printf("syntax error: unclosed double quote\n"), 0);
	if (!append_segment(acc, s, *i, j + 1))
		return (0);
	*i = j + 1;
	return (1);
}

/* BARE: copia fino a spazio/pipe/redir/quote */
int	read_bare_part(const char *s, int *i, char **acc)
{
	int	j;

	j = *i;
	while (s[j]
		&& !is_space(s[j])
		&& !is_pipe(s[j])
		&& !is_redir(s[j])
		&& s[j] != '\''
		&& s[j] != '"')
		j++;
	if (j == *i)
		return (0);
	if (!append_segment(acc, s, *i, j))
		return (0);
	*i = j;
	return (1);
}
