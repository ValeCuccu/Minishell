/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:37:26 by vacuccu           #+#    #+#             */
/*   Updated: 2025/10/27 16:33:20 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

static void	env_freeone(t_env *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->val);
	free(node);
}

void	free_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		env_freeone(env);
		env = next;
	}
}

t_env	*env_find_key(t_env *env, const char *key)
{
	while (env)
	{
		if (same_key(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*get_env_value(t_env *env, const char *name)
{
	t_env	*node;

	node = env_find_key(env, name);
	if (!node)
		return (NULL);
	return (node->val);
}

int	env_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}
