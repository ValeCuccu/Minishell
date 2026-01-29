/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2025/10/29 16:39:40 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

/*
** dup_or_empty:
**   se s != NULL -> duplica s
**   se s == NULL -> duplica stringa vuota ""
** Ritorna una stringa allocata o NULL se malloc fallisce.
*/
static char	*dup_or_empty(const char *s)
{
	if (s)
		return (ft_strdup(s));
	return (ft_strdup(""));
}

/*
** env_new_node:
**   alloca e riempie un nodo t_env con key/val copiati.
**   ritorna il nodo o NULL su errore malloc.
**
** Usata da init_env() per costruire la lista env.
*/
t_env	*env_new_node(const char *key, const char *val)
{
	t_env	*e;

	e = malloc(sizeof(*e));
	if (!e)
		return (NULL);
	e->key = dup_or_empty(key);
	e->val = dup_or_empty(val);
	if (!e->key || !e->val)
	{
		free(e->key);
		free(e->val);
		free(e);
		return (NULL);
	}
	e->next = NULL;
	return (e);
}

/*
** split_env_entry:
**   prende una stringa "KEY=VALUE"
**   e fa due malloc separati:
**     *out_key = "KEY"
**     *out_val = "VALUE"
**
** Se non c'è "=", allora:
**     *out_key = entry
**     *out_val = ""
**
** Ritorna:
**   0  se ok
**  -1  se malloc fallisce
*/
int	split_env_entry(const char *entry, char **out_key, char **out_val)
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
		return (-1);
	return (0);
}
