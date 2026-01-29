/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:31:20 by vacuccu           #+#    #+#             */
/*   Updated: 2025/12/12 18:23:41 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

static int	handle_special_dollar_out(const char *src, int *i, char **res)
{
	char	*val;

	if (src[*i + 1] == '?')
	{
		val = ft_itoa(get_last_status());
		if (!val)
			return (0);
		*res = join_and_free(*res, val);
		if (!*res)
		{
			free(val);
			return (0);
		}
		free(val);
		*i += 2;
		return (1);
	}
	if (!append_segment(res, src, *i, *i + 1))
		return (0);
	*i += 1;
	return (1);
}

int	expand_dollar_out(const char *src, int *i, char **res, t_env *env)
{
	int		end;
	char	*val;

	if (src[*i + 1] == '?' || !is_var_start(src[*i + 1]))
		return (handle_special_dollar_out(src, i, res));
	end = get_var_end(src, *i + 1);
	val = env_lookup(env, src + *i + 1, end - (*i + 1));
	if (!val)
		return (0);
	*res = join_and_free(*res, val);
	if (!*res)
		return (free(val), 0);
	free(val);
	*i = end;
	return (1);
}

static int	handle_special_dollar(const char *src, int *cur, char **res)
{
	char	*val;

	if (src[*cur + 1] == '?')
	{
		val = ft_itoa(get_last_status());
		if (!val)
			return (0);
		*res = join_and_free(*res, val);
		if (!*res)
		{
			free(val);
			return (0);
		}
		free(val);
		*cur += 2;
		return (1);
	}
	if (!append_segment(res, src, *cur, *cur + 1))
		return (0);
	*cur += 1;
	return (1);
}

int	expand_dq_dollar(const char *src, int *cur, char **res, t_env *env)
{
	int		end;
	char	*val;

	if (src[*cur + 1] == '?' || !is_var_start(src[*cur + 1]))
		return (handle_special_dollar(src, cur, res));
	end = get_var_end(src, *cur + 1);
	val = env_lookup(env, src + *cur + 1, end - (*cur + 1));
	if (!val)
		return (0);
	*res = join_and_free(*res, val);
	free(val);
	if (!*res)
		return (0);
	*cur = end;
	return (1);
}
