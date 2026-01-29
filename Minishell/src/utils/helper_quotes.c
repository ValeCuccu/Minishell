/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:38:04 by vacuccu           #+#    #+#             */
/*   Updated: 2025/10/27 16:05:01 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

int	dq_expand_at(const char *src, int *cur, char **res, t_env *env)
{
	if (!expand_dq_dollar(src, cur, res, env))
		return (0);
	return (1);
}

int	dq_finish(const char *src, int *i, int cur, char **res)
{
	if (!src[cur])
		return (0);
	if (!append_segment(res, src, *i, cur + 1))
		return (0);
	*i = cur + 1;
	return (1);
}
