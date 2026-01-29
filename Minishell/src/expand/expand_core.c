/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:50:13 by vacuccu           #+#    #+#             */
/*   Updated: 2025/12/12 18:22:30 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

int	handle_plain_text(const char *src, int *i, char **res, t_env *env)
{
	int	end;

	(void)env;
	end = *i;
	while (src[end] && src[end] != '\'' && src[end] != '"' && src[end] != '$')
		end++;
	if (!append_segment(res, src, *i, end))
		return (0);
	*i = end;
	return (1);
}

static int	append_plain_run(const char *src, int *i, char **res)
{
	int	start;

	start = *i;
	while (src[*i] && src[*i] != '\'' && src[*i] != '"' && src[*i] != '$')
		(*i)++;
	if (start == *i)
		return (1);
	if (!append_segment(res, src, start, *i))
		return (0);
	return (1);
}

static int	step_outside(const char *src, int *i, char **res, t_env *env)
{
	if (src[*i] == '\\' && src[*i + 1] == '$')
	{
		if (!append_char(res, '$'))
			return (0);
		*i += 2;
		return (1);
	}
	if (src[*i] == '\'')
		return (handle_single_quotes(src, i, res));
	if (src[*i] == '"')
		return (handle_double_quotes(src, i, res, env));
	if (src[*i] == '$')
		return (expand_dollar_out(src, i, res, env));
	return (append_plain_run(src, i, res));
}

char	*expand_out(const char *src, t_env *env)
{
	int		i;
	char	*res;
	int		before;

	res = NULL;
	i = 0;
	while (src && src[i])
	{
		before = i;
		if (!step_outside(src, &i, &res, env))
		{
			free(res);
			return (NULL);
		}
		if (i == before)
			i++;
	}
	if (res)
		return (res);
	return (ft_strdup(""));
}
