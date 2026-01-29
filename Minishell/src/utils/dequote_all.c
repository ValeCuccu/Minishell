/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:32:25 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/21 15:12:30 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

int	update_state(int state, char c)
{
	if (state == 0)
	{
		if (c == '\'')
			return (1);
		else if (c == '"')
			return (2);
	}
	else if (state == 1)
	{
		if (c == '\'')
			return (0);
	}
	else if (state == 2)
	{
		if (c == '"')
			return (0);
	}
	return (state);
}

char	*dequote_all(const char *s)
{
	int		i;
	int		state;
	char	*out;

	i = 0;
	state = 0;
	out = NULL;
	while (s && s[i])
	{
		if ((state == 0 && (s[i] == '\'' || s[i] == '"'))
			|| (state == 1 && s[i] == '\'')
			|| (state == 2 && s[i] == '"'))
			state = update_state(state, s[i]);
		else if (!append_char(&out, s[i]))
			return (NULL);
		i++;
	}
	if (state != 0)
	{
		free(out);
		return (NULL);
	}
	if (!out)
		return (ft_strdup(""));
	return (out);
}
