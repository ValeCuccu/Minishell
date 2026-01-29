/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:42:35 by vacuccu           #+#    #+#             */
/*   Updated: 2025/10/29 16:16:16 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!(s1[i] == '\0' && s2[i] == '\0'))
		return (1);
	return (0);
}

int	is_builtin(char *s)
{
	if (!s)
		return (0);
	if (ft_strcmp(s, "echo") == 0)
		return (1);
	if (ft_strcmp(s, "cd") == 0)
		return (1);
	if (ft_strcmp(s, "pwd") == 0)
		return (1);
	if (ft_strcmp(s, "export") == 0)
		return (1);
	if (ft_strcmp(s, "unset") == 0)
		return (1);
	if (ft_strcmp(s, "env") == 0)
		return (1);
	if (ft_strcmp(s, "exit") == 0)
		return (1);
	return (0);
}

int	count_words_until_pipe(const t_token *t)
{
	int	c;

	c = 0;
	while (t && t->type != T_PIPE)
	{
		if (t ->type == T_WORD)
			c++;
		if (t->type == T_HEREDOC || t->type == T_REDIR_IN
			|| t->type == T_REDIR_OUT || t->type == T_APPEND)
		{
			if (t->next && t->next->type == T_WORD)
				t = t->next;
		}
		t = t->next;
	}
	return (c);
}

int	map_tok_to_redir(t_toktype op, t_redir_type *out)
{
	if (op == T_REDIR_IN)
		*out = REDIR_IN;
	else if (op == T_REDIR_OUT)
		*out = REDIR_OUT;
	else if (op == T_APPEND)
		*out = REDIR_APPEND;
	else if (op == T_HEREDOC)
		*out = REDIR_HEREDOC;
	else
		return (0);
	return (1);
}

int	attach_redir(t_cmd *cmd, t_toktype op, const t_token *word_tok)
{
	t_redir_type	rtype;
	int				expand;
	t_redir			*node;

	if (!cmd || !word_tok || !word_tok->input)
		return (0);
	if (!map_tok_to_redir(op, &rtype))
		return (0);
	expand = 1;
	if (rtype == REDIR_HEREDOC)
	{
		if (word_tok->was_quoted)
			expand = 0;
		else
			expand = 1;
	}
	node = redir_new(rtype, word_tok->input, expand);
	if (!node)
		return (0);
	redir_append(&cmd->redirs, node);
	return (1);
}
