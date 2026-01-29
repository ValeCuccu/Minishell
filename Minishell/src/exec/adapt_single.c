/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapt_single.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:30:00 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/21 12:18:40 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <sys/wait.h>
#include <errno.h>

static int	is_exit_builtin(char **av)
{
	if (!av || !av[0])
		return (0);
	return (ft_strcmp(av[0], "exit") == 0);
}

static int	ap_run_single_parent_builtin(t_cmd *line, t_env **penv)
{
	int	sv[2];
	int	st;

	if (is_exit_builtin(line->av) && line->redirs == NULL)
		return (bi_run_parent(line->av, penv));
	if (save_stdio(sv) < 0)
		return (1);
	if (ap_apply_redirs(line->redirs) < 0)
	{
		restore_stdio(sv);
		return (1);
	}
	st = bi_run_parent(line->av, penv);
	restore_stdio(sv);
	return (st);
}

static void	ap_run_single_child(t_cmd *line, t_env **penv)
{
	int	ec;

	ec = ap_run_child_exec(line, penv);
	if (line)
		free_cmd_list(line);
	if (penv && *penv)
		free_env_list(*penv);
	_exit(ec);
}

static int	ap_run_single_wait(pid_t pid)
{
	int	st;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (waitpid(pid, &st, 0) < 0)
		return (err_msg("waitpid", strerror(errno)), 1);
	setup_signals_interactive();
	return (status_from_wait(st));
}

int	ap_run_single(t_cmd *line, t_env **penv)
{
	pid_t	pid;

	if (ap_is_parent_affecting_builtin(line->av) || line->is_builtin == 1)
		return (ap_run_single_parent_builtin(line, penv));
	pid = fork();
	if (pid < 0)
		return (err_msg("fork", strerror(errno)), 1);
	if (pid == 0)
		ap_run_single_child(line, penv);
	return (ap_run_single_wait(pid));
}
