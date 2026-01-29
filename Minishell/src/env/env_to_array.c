/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:15:17 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/20 15:23:29 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

static int	env_count(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		n++;
		env = env->next;
	}
	return (n);
}

static void	free_envp_partial(char **envp, int i)
{
	while (i > 0)
	{
		i--;
		free(envp[i]);
	}
	free(envp);
}

static char	*join_kv(const char *k, const char *v)
{
	char	*tmp;
	char	*kv;

	tmp = ft_strjoin(k, "=");
	if (!tmp)
		return (NULL);
	if (v && *v)
		kv = ft_strjoin(tmp, v);
	else
		kv = ft_strdup(tmp);
	free(tmp);
	return (kv);
}

static int	fill_envv(t_env *env, char **envp, int n)
{
	int		i;
	char	*kv;

	i = 0;
	while (i < n)
	{
		kv = join_kv(env->key, env->val);
		if (!kv)
		{
			free_envp_partial(envp, i);
			return (-1);
		}
		envp[i] = kv;
		i++;
		env = env->next;
	}
	return (0);
}

char	**env_to_envp_array(t_env *env)
{
	int		n;
	int		i;
	char	**envp;

	n = env_count(env);
	envp = malloc(sizeof(char *) * (n + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < n)
	{
		envp[i] = NULL;
		i++;
	}
	envp[n] = NULL;
	if (fill_envv(env, envp, n) == -1)
	{
		free_envp_array(envp);
		return (NULL);
	}
	return (envp);
}
