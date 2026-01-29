/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:14:48 by vacuccu           #+#    #+#             */
/*   Updated: 2025/12/12 18:14:56 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

/*
** free_env_list:
**   libera tutta la lista t_env:
**     - libera key e val
**     - libera ogni nodo
*/
void	free_env_list(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->val);
		free(env);
		env = next;
	}
}

/*
** env_get_value:
**   cerca una chiave nell'env e ritorna il suo valore.
**   se non esiste, ritorna NULL.
**
**   es: key="PATH"  -> "/usr/bin:/bin"
*/
char	*env_get_value(t_env *env, const char *key)
{
	size_t	len;

	if (!key)
		return (NULL);
	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->key, key, len) == 0 && env->key[len] == '\0')
			return (env->val);
		env = env->next;
	}
	return (NULL);
}
