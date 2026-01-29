/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:00:00 by anpastac          #+#    #+#             */
/*   Updated: 2026/01/23 09:36:08 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

char	*hd_expand_dollar(const char *s, size_t *i, t_env *env)
{
	size_t	start;
	char	*name;
	char	*val;
	char	*out;

	(*i)++;
	if (s[*i] == '?')
		return ((*i)++, ft_itoa(get_last_status()));
	if (!hd_is_name_start(s[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (s[*i] && hd_is_name_char(s[*i]))
		(*i)++;
	name = ft_substr(s, start, *i - start);
	if (!name)
		return (NULL);
	val = env_get_value(env, name);
	if (val)
		out = ft_strdup(val);
	else
		out = ft_strdup("");
	free(name);
	return (out);
}

char	*hd_expand_step(const char *s, size_t *i, t_env *env, char *acc)
{
	char	*tmp;

	if (s[*i] == '$')
	{
		tmp = hd_expand_dollar(s, i, env);
		if (!tmp)
			return (free(acc), NULL);
		acc = hd_append_str(acc, tmp);
		free(tmp);
		if (!acc)
			return (NULL);
		return (acc);
	}
	acc = hd_append_char(acc, s[*i]);
	(*i)++;
	if (!acc)
		return (NULL);
	return (acc);
}

char	*hd_expand_vars(const char *s, t_env *env)
{
	size_t	i;
	char	*acc;

	(void)env;
	if (!s)
		return (NULL);
	i = 0;
	acc = NULL;
	while (s[i])
	{
		acc = hd_expand_step(s, &i, env, acc);
		if (!acc)
			return (NULL);
	}
	if (!acc)
		return (ft_strdup(""));
	return (acc);
}
