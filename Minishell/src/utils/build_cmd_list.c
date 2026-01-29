/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:39:00 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/09 18:43:55 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

t_cmd	*build_cmd_list(t_token *lst)
{
	t_cmd	*head;
	t_cmd	*cur;
	t_token	*it;

	head = NULL;
	it = lst;
	while (it)
	{
		cur = new_cmd(NULL);
		if (!cur)
			return (free_cmd_list(head), NULL);
		if (!fill_argv_for_cmd(cur, &it))
			return (cmd_free(cur), free_cmd_list(head), NULL);
		cmd_append(&head, cur);
		if (it && it->type == T_PIPE)
			it = it->next;
	}
	return (head);
}

void	set_builtin_flag(t_cmd *cmd)
{
	cmd->is_builtin = 0;
	if (cmd->av && cmd->av[0] && is_builtin(cmd->av[0]))
		cmd->is_builtin = 1;
}
