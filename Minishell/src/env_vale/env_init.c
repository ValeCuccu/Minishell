/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:23:53 by vacuccu           #+#    #+#             */
/*   Updated: 2025/10/29 16:05:14 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*env_new(char *key, char *val)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->val = val;
	node->next = NULL;
	return (node);
}

void	env_add_back(t_env **lst, t_env *new_node)
{
	t_env	*tmp;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

static t_env	*env_from_string(const char *s)
{
	int		i;
	char	*key;
	char	*val;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	key = ft_substr(s, 0, i);
	if (!key)
		return (NULL);
	if (s[i] == '=')
		val = ft_strdup(s + i + 1);
	else
		val = ft_strdup("");
	if (!val)
	{
		free(key);
		return (NULL);
	}
	return (env_new(key, val));
}

t_env	*build_env(char **envp)
{
	t_env	*env;
	t_env	*node;
	int		i;

	env = NULL;
	i = 0;
	while (envp && envp[i])
	{
		node = env_from_string(envp[i]);
		if (!node)
		{
			free_env(env);
			return (NULL);
		}
		env_add_back(&env, node);
		i++;
	}
	return (env);
}
