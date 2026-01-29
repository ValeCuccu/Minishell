/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:28:12 by vacuccu           #+#    #+#             */
/*   Updated: 2025/10/24 15:09:30 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

int	append_or_heredoc(const char *s, int *i, t_toktype *type)
{
	if (!s || !i || !type)
		return (0);
	if (s[*i] == '\0')
		return (0);
	if (s[*i + 1] == '\0')
		return (0);
	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		*type = T_HEREDOC;
		*i += 2;
		return (1);
	}
	else if (s[*i] == '>' && s[*i + 1] == '>')
	{
		*type = T_APPEND;
		*i += 2;
		return (1);
	}
	return (0);
}

int	read_single_redir(const char *s, int *i, t_toktype *type)
{
	if (!s || !i || !type)
		return (0);
	if (s[*i] == '\0')
		return (0);
	if (s[*i] == '<')
	{
		*type = T_REDIR_IN;
		*i += 1;
		return (1);
	}
	if (s[*i] == '>')
	{
		*type = T_REDIR_OUT;
		*i += 1;
		return (1);
	}
	return (0);
}

int	read_pipe(const char *s, int *i, t_toktype *type)
{
	if (!s || !i || !type)
		return (0);
	if (s[*i] == '\0')
		return (0);
	if (s[*i] == '|')
	{
		*type = T_PIPE;
		*i += 1;
		return (1);
	}
	return (0);
}

int	read_operator(const char *s, int *i, t_toktype *out)
{
	if (!s || !i || !out)
		return (0);
	if (s[*i] == '\0')
		return (0);
	if (append_or_heredoc(s, i, out))
		return (1);
	if (read_pipe(s, i, out))
		return (1);
	if (read_single_redir(s, i, out))
		return (1);
	return (0);
}
