/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:54:12 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/20 15:28:02 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

void	skip_spaces(const char *s, int *i)
{
	while (s[*i] && is_space(s[*i]))
		(*i)++;
}

int	read_word(const char *s, int *i, char **out)
{
	char	*acc;

	acc = NULL;
	while (s[*i] && !is_space(s[*i]) && !is_pipe(s[*i]) && !is_redir(s[*i]))
	{
		if (!read_word_part(s, i, &acc))
		{
			if (acc)
				free(acc);
			return (0);
		}
	}
	*out = acc;
	return (acc != NULL);
}

int	next_token(const char *s, int *i, t_token **out)
{
	t_toktype	type;
	char		*word;

	if (read_operator(s, i, &type))
	{
		*out = token_new(type, NULL);
		return (*out != NULL);
	}
	if (read_word(s, i, &word))
	{
		*out = token_new(T_WORD, word);
		free(word);
		return (*out != NULL);
	}
	return (0);
}

int	push_token(t_token **head, t_token *node)
{
	if (!node)
		return (0);
	if (!token_append(head, node))
	{
		token_clear(head);
		return (0);
	}
	return (1);
}

t_token	*lex_line(const char *s)
{
	t_token	*head;
	t_token	*node;
	int		i;

	head = NULL;
	i = 0;
	while (s && s[i])
	{
		skip_spaces(s, &i);
		if (!s[i])
			break ;
		if (!next_token(s, &i, &node))
		{
			token_clear(&head);
			return (NULL);
		}
		if (!push_token(&head, node))
			return (NULL);
	}
	return (head);
}

/* int	is_blank(char c)
{
	return (c == ' ' || c == '\t');
} */
