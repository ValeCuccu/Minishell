/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:23:16 by vacuccu           #+#    #+#             */
/*   Updated: 2025/10/24 15:08:46 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

t_token	*token_new(t_toktype type, const char *text)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		return (NULL);
	node->type = type;
	if (text != NULL)
		node->input = ft_strdup(text);
	else
		node->input = ft_strdup("");
	if (node->input == NULL)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

int	token_append(t_token **head, t_token *node)
{
	t_token	*cur;

	if (head == NULL || node == NULL)
		return (0);
	if (*head == NULL)
	{
		*head = node;
		return (1);
	}
	cur = *head;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = node;
	return (1);
}

void	token_clear(t_token **head)
{
	t_token	*cur;
	t_token	*next;

	if (head == NULL || *head == NULL)
		return ;
	cur = *head;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->input != NULL)
			free(cur->input);
		free(cur);
		cur = next;
	}
	*head = NULL;
}

void	free_token_list(t_token *lst)
{
	t_token	*nx;

	while (lst)
	{
		nx = lst->next;
		if (lst->input)
			free(lst->input);
		free(lst);
		lst = nx;
	}
}

const char	*tok_type_name(t_toktype t)
{
	if (t == T_WORD)
		return ("WORD");
	if (t == T_PIPE)
		return ("PIPE");
	if (t == T_REDIR_IN)
		return ("REDIR_IN");
	if (t == T_REDIR_OUT)
		return ("REDIR_OUT");
	if (t == T_APPEND)
		return ("APPEND");
	if (t == T_HEREDOC)
		return ("HEREDOC");
	return ("?");
}
