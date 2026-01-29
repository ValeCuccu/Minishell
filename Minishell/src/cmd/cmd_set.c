/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:21:09 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/12 17:52:46 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

t_cmd	*new_cmd(char **av)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->av = av;
	cmd->is_builtin = 0;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	cmd_append(t_cmd **cmd_list, t_cmd *new_node)
{
	t_cmd	*current;

	if (!new_node || !cmd_list)
		return ;
	new_node->next = NULL;
	if (!*cmd_list)
	{
		*cmd_list = new_node;
		return ;
	}
	current = *cmd_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	cmd_free(t_cmd *cmd_node)
{
	int	index;

	if (!cmd_node)
		return ;
	if (cmd_node->av)
	{
		index = 0;
		while (cmd_node->av[index])
		{
			free(cmd_node->av[index]);
			index++;
		}
		free(cmd_node->av);
	}
	redir_clear(&(cmd_node->redirs));
	free(cmd_node);
}

void	cmd_clear(t_cmd **cmd_list)
{
	t_cmd	*current;
	t_cmd	*next_node;

	if (!cmd_list || !*cmd_list)
		return ;
	current = *cmd_list;
	while (current)
	{
		next_node = current->next;
		cmd_free(current);
		current = next_node;
	}
	*cmd_list = NULL;
}

void	free_cmd_list(t_cmd *cmds)
{
	t_cmd	*nx;

	while (cmds)
	{
		nx = cmds->next;
		cmd_free(cmds);
		cmds = nx;
	}
}
