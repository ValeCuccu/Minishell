/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:24:57 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/20 15:28:50 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

t_redir	*redir_new(t_redir_type type, const char *filename, int expand)
{
	t_redir	*redir_node;

	redir_node = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_node)
		return (NULL);
	redir_node->type = type;
	if (filename)
		redir_node->filename = ft_strdup(filename);
	else
		redir_node->filename = NULL;
	if (filename && !redir_node->filename)
	{
		free (redir_node);
		return (NULL);
	}
	redir_node->expand = expand;
	redir_node->next = NULL;
	return (redir_node);
}

void	redir_append(t_redir **lst, t_redir *new_node)
{
	t_redir	*cur;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new_node;
}

void	redir_free(t_redir *r)
{
	if (!r)
		return ;
	free(r->filename);
	free(r);
}

void	redir_clear(t_redir **redir_list)
{
	t_redir	*current;
	t_redir	*next_node;

	if (!redir_list)
		return ;
	current = *redir_list;
	while (current)
	{
		next_node = current->next;
		redir_free(current);
		current = next_node;
	}
	*redir_list = NULL;
}
