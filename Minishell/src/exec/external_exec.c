/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2026/01/21 12:24:11 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

int	exec_external(char **argv, char **envp, t_env *env_list)
{
	char	*path;
	int		status;

	if (!argv || !argv[0] || !argv[0][0])
		return (127);
	path = prepare_exec_path(argv, env_list);
	if (!path)
	{
		cmd_error(argv[0], "command not found");
		return (127);
	}
	execve(path, argv, envp);
	if (errno == ENOEXEC)
		try_exec_sh(path, envp);
	status = report_exec_error(path, argv[0]);
	free(path);
	return (status);
}
