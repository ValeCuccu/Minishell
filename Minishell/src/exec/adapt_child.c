/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapt_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2026/01/21 12:12:17 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <errno.h>

int	ap_run_child_exec(t_cmd *c, t_env **penv)
{
	char	**envp;
	int		st;

	setup_signals_child();
	if (ap_apply_redirs(c->redirs) < 0)
		return (1);
	if (c->is_builtin == 1)
		return (bi_run_child(c->av, penv));
	envp = env_to_envp_array(*penv);
	if (envp == NULL)
		return (err_msg("env", "alloc"), 1);
	st = exec_external(c->av, envp, *penv);
	free_envp_array(envp);
	return (st);
}

void	ap_child_exit(int ec, t_cmd *cmd_head, t_env *env, pid_t *pids)
{
	ms_close_extra_fds();
	if (cmd_head)
		free_cmd_list(cmd_head);
	if (env)
		free_env_list(env);
	if (pids)
		free(pids);
	_exit(ec);
}
