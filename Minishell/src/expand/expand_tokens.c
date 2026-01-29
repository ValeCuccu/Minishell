/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:02:27 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/22 13:53:15 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

static int	has_quoted(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static int	handle_heredoc_delim(t_token *cur)
{
	char	*clean;
	int		had;

	had = has_quoted(cur->input);
	clean = dequote_all(cur->input);
	if (!clean)
		return (0);
	free(cur->input);
	cur->input = clean;
	cur->was_quoted = had;
	return (1);
}

static int	handle_normal_word(t_token *cur, t_env *env)
{
	char	*expanded;
	char	*clean;
	int		had;

	had = has_quoted(cur->input);
	expanded = expand_out(cur->input, env);
	if (!expanded)
		return (0);
	clean = dequote_all(expanded);
	free(expanded);
	if (!clean)
		return (0);
	if (clean[0] == '\0' && had == 0)
	{
		free(clean);
		free(cur->input);
		cur->input = NULL;
		return (-1);
	}
	free(cur->input);
	cur->input = clean;
	cur->was_quoted = had;
	return (1);
}

static int	expand_one_token(t_token *cur, t_token *prev, t_env *env)
{
	if (cur->type != T_WORD)
		return (1);
	if (prev && prev->type == T_HEREDOC)
		return (handle_heredoc_delim(cur));
	return (handle_normal_word(cur, env));
}

int	expand_tokens(t_token **plist, t_env *env)
{
	t_token		*prev;
	t_token		*cur;
	t_token		*next;
	int			st;

	prev = NULL;
	cur = *plist;
	while (cur)
	{
		next = cur->next;
		st = expand_one_token(cur, prev, env);
		if (st == 0)
			return (0);
		if (st == -1)
		{
			remove_token(plist, prev);
		}
		else
		{
			prev = cur;
		}
		cur = next;
	}
	return (1);
}
