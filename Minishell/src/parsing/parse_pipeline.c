/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:42:04 by vacuccu           #+#    #+#             */
/*   Updated: 2025/12/12 18:33:09 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parse_input(const char *line, t_env *env, int *exit_status)
{
	t_token	*tk;
	t_cmd	*cmds;

	tk = lexer_build_tokens(line);
	if (!tk)
		return (NULL);
	if (!expand_tokens(&tk, env))
	{
		free_token_list(tk);
		return (NULL);
	}
	if (check_syntax_errors(tk, exit_status))
	{
		free_token_list(tk);
		return (NULL);
	}
	cmds = build_cmd_list(tk);
	free_token_list(tk);
	return (cmds);
}
