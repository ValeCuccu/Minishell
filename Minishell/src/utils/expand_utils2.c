/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:34:50 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/21 15:12:11 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

void	remove_token(t_token **plist, t_token *prev)
{
	t_token	*cur;

	if (!plist || !*plist)
		return ;
	if (prev == NULL)
	{
		cur = *plist;
		*plist = cur->next;
		free(cur->input);
		free(cur);
	}
	else
	{
		cur = prev->next;
		if (!cur)
			return ;
		prev->next = cur->next;
		free(cur->input);
		free(cur);
	}
}
