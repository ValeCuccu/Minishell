/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:35:42 by vacuccu           #+#    #+#             */
/*   Updated: 2025/12/09 16:50:59 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

int	handle_single_quotes(const char *src, int *i, char **res)
{
	int	end;

	end = *i + 1;
	while (src[end] && src[end] != '\'')
		end++;
	if (!src[end])
		return (0);
	if (!append_segment(res, src, *i, end + 1))
		return (0);
	*i = end + 1;
	return (1);
}

int	handle_double_quotes(const char *src, int *i, char **res, t_env *env)
{
	int	cur;

	cur = *i + 1;
	while (src[cur] && src[cur] != '"')
	{
		if (src[cur] == '$'
			&& (src[cur + 1] == '?' || is_var_start(src[cur + 1])))
		{
			if (!append_segment(res, src, *i, cur))
				return (0);
			if (!dq_expand_at(src, &cur, res, env))
				return (0);
			*i = cur;
			continue ;
		}
		cur++;
	}
	return (dq_finish(src, i, cur, res));
}

static int	process_step(const char *src, int *i, char **res, t_env *env)
{
	int	status;

	if (src[*i] == '\'')
		status = handle_single_quotes(src, i, res);
	else if (src[*i] == '"')
		status = handle_double_quotes(src, i, res, env);
	else
		status = handle_plain_text(src, i, res, env);
	if (!status)
		return (0);
	return (1);
}

char	*expand_quotes(const char *src, t_env *env)
{
	int		i;
	char	*res;

	res = NULL;
	i = 0;
	while (src && src[i])
	{
		if (!process_step(src, &i, &res, env))
		{
			free(res);
			return (NULL);
		}
	}
	if (res)
		return (res);
	return (ft_strdup(""));
}
