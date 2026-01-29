/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:24:32 by vacuccu           #+#    #+#             */
/*   Updated: 2025/10/29 16:22:36 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_update_value(t_env *node, const char *val)
{
	char	*new_val;

	new_val = ft_strdup(val);
	if (!new_val)
		return (-1);
	free(node->val);
	node->val = new_val;
	return (0);
}

int	env_add_new(t_env **env, const char *key, const char *val)
{
	t_env	*node;
	char	*new_key;
	char	*new_val;

	new_key = ft_strdup(key);
	new_val = ft_strdup(val);
	if (!new_key || !new_val)
	{
		free(new_key);
		free(new_val);
		return (-1);
	}
	node = env_new(new_key, new_val);
	if (!node)
	{
		free(new_key);
		free(new_val);
		return (-1);
	}
	env_add_back(env, node);
	return (0);
}

int	env_set(t_env **env, const char *key, const char *val)
{
	t_env	*node;

	if (!env || !key || !val)
		return (-1);
	node = env_find_key(*env, key);
	if (node)
		return (env_update_value(node, val));
	return (env_add_new(env, key, val));
}

int	env_unset(t_env **env, char *key)
{
	t_env	*cur;
	t_env	*prev;

	if (!env || !*env || !key)
		return (0);
	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (same_key(cur->key, key))
		{
			if (!prev)
				*env = cur->next;
			else
				prev->next = cur->next;
			free(cur->key);
			free(cur->val);
			free(cur);
			return (1);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
