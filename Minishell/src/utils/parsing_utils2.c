/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:09:27 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/20 15:29:59 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

static int	process_token_for_cmd(t_cmd *cmd, t_token **tptr, int *i)
{
	t_token	*t;

	t = *tptr;
	if (t->type == T_WORD)
	{
		cmd->av[*i] = ft_strdup(t->input);
		if (!cmd->av[*i])
			return (0);
		(*i)++;
	}
	else if (t->type == T_REDIR_IN || t->type == T_REDIR_OUT
		|| t->type == T_APPEND || t->type == T_HEREDOC)
	{
		if (!t->next || t->next->type != T_WORD)
			return (0);
		if (!attach_redir(cmd, t->type, t->next))
			return (0);
		*tptr = t->next;
	}
	return (1);
}

static void	free_strarray_partial(char **arr, int used)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < used)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	fill_argv_loop(t_cmd *cmd, t_token **t, int *i)
{
	while (*t && (*t)->type != T_PIPE)
	{
		if (!process_token_for_cmd(cmd, t, i))
		{
			free_strarray_partial(cmd->av, *i);
			free(cmd->av);
			cmd->av = NULL;
			return (0);
		}
		*t = (*t)->next;
	}
	return (1);
}

int	fill_argv_for_cmd(t_cmd *cmd, t_token **it)
{
	int		n;
	int		i;
	t_token	*t;

	if (!cmd || !it)
		return (0);
	n = count_words_until_pipe(*it);
	cmd->av = (char **)malloc(sizeof(char *) * (n + 1));
	if (!cmd->av)
		return (0);
	i = 0;
	while (i < n + 1)
	{
		cmd->av[i] = NULL;
		i++;
	}
	i = 0;
	t = *it;
	if (!fill_argv_loop(cmd, &t, &i))
		return (0);
	cmd->av[i] = NULL;
	set_builtin_flag(cmd);
	*it = t;
	return (1);
}
