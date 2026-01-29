/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2026/01/20 15:25:55 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

/*
** env_update_existing:
**   cerca 'key' nella lista env
**   se la trova:
**     - duplica il nuovo valore (o stringa vuota se val == NULL)
**     - libera il vecchio env->val
**     - salva quello nuovo
**     - ritorna 1 (aggiornato)
**   se non trova:
**     - ritorna 0
**   se malloc fallisce:
**     - ritorna -1
*/
static int	env_update_existing(t_env *env, const char *key, const char *val)
{
	char	*new_val;
	size_t	len;

	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->key, key, len) == 0 && env->key[len] == '\0')
		{
			if (val)
				new_val = ft_strdup(val);
			else
				new_val = ft_strdup("");
			if (!new_val)
				return (-1);
			free(env->val);
			env->val = new_val;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

static int	env_insert_new(t_env **env, const char *key, const char *val)
{
	t_env	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (-1);
	node->key = ft_strdup(key);
	if (val)
		node->val = ft_strdup(val);
	else
		node->val = ft_strdup("");
	if (!node->key || !node->val)
	{
		free(node->key);
		free(node->val);
		free(node);
		return (-1);
	}
	node->next = *env;
	*env = node;
	return (0);
}

int	env_set_value(t_env **env, const char *key, const char *val)
{
	int	r;

	if (!env || !key)
		return (-1);
	r = env_update_existing(*env, key, val);
	if (r == 1)
		return (0);
	if (r == -1)
		return (-1);
	return (env_insert_new(env, key, val));
}

static t_env	*find_prev_env_node(t_env *env, const char *key,
					t_env **out_prev)
{
	t_env	*cur;
	size_t	len;

	*out_prev = NULL;
	cur = env;
	len = ft_strlen(key);
	while (cur)
	{
		if (ft_strncmp(cur->key, key, len) == 0 && cur->key[len] == '\0')
			return (cur);
		*out_prev = cur;
		cur = cur->next;
	}
	return (NULL);
}

int	env_unset_key(t_env **env, const char *key)
{
	t_env	*cur;
	t_env	*prev;

	if (!env || !*env || !key)
		return (0);
	cur = find_prev_env_node(*env, key, &prev);
	if (!cur)
		return (0);
	if (prev)
		prev->next = cur->next;
	else
		*env = cur->next;
	free(cur->key);
	free(cur->val);
	free(cur);
	return (0);
}
