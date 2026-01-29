/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_exec_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:21:14 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/21 15:09:23 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

void	try_exec_sh(char *path, char **envp)
{
	char	*sh_argv[3];

	sh_argv[0] = "sh";
	sh_argv[1] = path;
	sh_argv[2] = NULL;
	execve("/bin/sh", sh_argv, envp);
}

int	is_directory(const char *p)
{
	struct stat	st;

	if (stat(p, &st) == -1)
		return (0);
	if (S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

void	cmd_error(char *cmd, char *msg)
{
	err_msg(cmd, msg);
}

char	*prepare_exec_path(char **argv, t_env *env_list)
{
	if (!argv || !argv[0])
		return (NULL);
	if (ft_strchr(argv[0], '/'))
		return (ft_strdup(argv[0]));
	return (resolve_cmd_path(argv[0], env_list));
}

int	report_exec_error(char *path, char *cmd)
{
	if (errno == EISDIR)
	{
		cmd_error(cmd, "Is a directory");
		return (126);
	}
	if (errno == EACCES)
	{
		if (is_directory(path))
			cmd_error(cmd, "Is a directory");
		else
			cmd_error(cmd, "Permission denied");
		return (126);
	}
	if (errno == ENOENT)
	{
		if (ft_strchr(cmd, '/'))
			cmd_error(cmd, "No such file or directory");
		else
			cmd_error(cmd, "command not found");
		return (127);
	}
	cmd_error(cmd, strerror(errno));
	return (126);
}
