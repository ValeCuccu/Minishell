/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:02:13 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/21 15:02:49 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

int	status_from_wait(int st)
{
	int	signo;

	if (WIFSIGNALED(st))
	{
		signo = WTERMSIG(st);
		return (128 + signo);
	}
	if (WIFEXITED(st))
		return (WEXITSTATUS(st));
	return (1);
}

void	set_last_status(t_env **penv, int code)
{
	char	*s;

	s = ft_itoa(code);
	if (!s)
		return ;
	env_set_value(penv, "?", s);
	free(s);
}

void	wait_all_and_set_status(pid_t *pid_arr, int nproc, t_env **penv)
{
	int		i;
	int		st;
	int		last_status;
	pid_t	last_pid;
	pid_t	got;

	if (nproc <= 0)
		return ;
	last_pid = pid_arr[nproc - 1];
	last_status = 0;
	i = 0;
	while (i < nproc)
	{
		got = waitpid(pid_arr[i], &st, 0);
		if (got == last_pid)
			last_status = status_from_wait(st);
		i++;
	}
	set_last_status(penv, last_status);
}
