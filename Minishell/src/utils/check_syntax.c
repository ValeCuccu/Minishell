/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:22:23 by vacuccu           #+#    #+#             */
/*   Updated: 2025/10/24 15:08:59 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

static int	is_redir_type(t_toktype t)
{
	if (t == T_REDIR_IN || t == T_REDIR_OUT
		|| t == T_APPEND || t == T_HEREDOC)
		return (1);
	return (0);
}

static int	syntax_error(int *exit_status)
{
	ft_putstr_fd("minishell: syntax error\n", 2);
	if (exit_status)
		*exit_status = 2;
	return (1);
}

int	check_syntax_errors(t_token *t, int *exit_status)
{
	t_token	*cur;

	if (!t)
		return (0);
	if (t->type == T_PIPE)
		return (syntax_error(exit_status));
	cur = t;
	while (cur)
	{
		if (cur->type == T_PIPE
			&& (!cur->next || cur->next->type == T_PIPE))
			return (syntax_error(exit_status));
		if (is_redir_type(cur->type)
			&& (!cur->next || cur->next->type != T_WORD))
			return (syntax_error(exit_status));
		if (!cur->next)
			break ;
		cur = cur->next;
	}
	if (cur && cur->type == T_PIPE)
		return (syntax_error(exit_status));
	return (0);
}
