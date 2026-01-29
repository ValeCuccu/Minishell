/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:10:00 by anpastac          #+#    #+#             */
/*   Updated: 2026/01/20 18:10:00 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

/*
** NOTE:
** env_get_value() ritorna un puntatore interno (env->val).
** Quindi NON free() mai su HOME/OLDPWD presi dall'env.
*/

int	cd_err(const char *msg)
{
	ap_err_msg("cd", msg);
	return (1);
}

static int	cd_err_path(const char *path)
{
	ap_err_msg_quoted("cd", (char *)path, strerror(errno));
	return (1);
}

static int	cd_update_pwd(t_env **penv, const char *oldpwd_str)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (cd_err(strerror(errno)));
	if (oldpwd_str && oldpwd_str[0] != '\0')
	{
		if (env_set_value(penv, "OLDPWD", oldpwd_str) < 0)
			return (free(cwd), cd_err("env_set_value failed"));
	}
	if (env_set_value(penv, "PWD", cwd) < 0)
		return (free(cwd), cd_err("env_set_value failed"));
	free(cwd);
	return (0);
}

int	cd_chdir_and_update(t_env **penv, const char *path, char *oldpwd_heap)
{
	int	ret;

	ret = 0;
	if (!oldpwd_heap)
		oldpwd_heap = ft_strdup("");
	if (!oldpwd_heap)
		return (cd_err("alloc"));
	if (chdir(path) == -1)
		ret = cd_err_path(path);
	else if (cd_update_pwd(penv, oldpwd_heap) != 0)
		ret = 1;
	free(oldpwd_heap);
	return (ret);
}
