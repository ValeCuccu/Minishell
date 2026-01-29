/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonio <student.42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 00:00:00 by antonio           #+#    #+#             */
/*   Updated: 2025/10/28 00:00:00 by antonio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

static int	split_key_val(const char *entry,
				char **out_key, char **out_val)
{
	char	*eq;

	*out_key = NULL;
	*out_val = NULL;
	eq = ft_strchr(entry, '=');
	if (eq)
	{
		*out_key = ft_substr(entry, 0, (size_t)(eq - entry));
		*out_val = ft_strdup(eq + 1);
	}
	else
	{
		*out_key = ft_strdup(entry);
		*out_val = ft_strdup("");
	}
	if (!*out_key || !*out_val)
	{
		free(*out_key);
		free(*out_val);
		return (-1);
	}
	return (0);
}

static t_env	*new_env_node(char *key, char *val)
{
	t_env	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->key = key;
	node->val = val;
	node->next = NULL;
	return (node);
}

static void	append_env_node(t_env **head, t_env **tail, t_env *node)
{
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
}

static int	process_env_entry(char *entry, t_env **head, t_env **tail)
{
	t_env	*node;
	char	*key;
	char	*val;

	if (split_key_val(entry, &key, &val) == -1)
	{
		free_env_list(*head);
		return (-1);
	}
	node = new_env_node(key, val);
	if (!node)
	{
		free(key);
		free(val);
		free_env_list(*head);
		return (-1);
	}
	append_env_node(head, tail, node);
	return (0);
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*tail;

	head = NULL;
	tail = NULL;
	while (envp && *envp)
	{
		if (process_env_entry(*envp, &head, &tail) == -1)
			return (NULL);
		envp++;
	}
	return (head);
}
