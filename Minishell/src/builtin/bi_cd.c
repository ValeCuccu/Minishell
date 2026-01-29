/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 00:00:00 by anpastac          #+#    #+#             */
/*   Updated: 2026/01/21 15:01:24 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

int	bi_cd(char **av, t_env **penv)
{
	char		*oldpwd_heap;
	const char	*pwd_env;

	if (!penv || !*penv)
		return (cd_err("internal env is NULL"));
	if (av && av[1] && av[2])
		return (cd_err("too many arguments"));
	oldpwd_heap = get_oldpwd_snapshot(*penv);
	if (!av || !av[1])
		return (cd_to_home(penv, oldpwd_heap));
	if (ft_strcmp(av[1], "-") == 0)
		return (cd_to_oldpwd(penv, oldpwd_heap));
	pwd_env = (const char *)av[1];
	return (cd_chdir_and_update(penv, pwd_env, oldpwd_heap));
}

char	*get_oldpwd_snapshot(t_env *env)
{
	char		*oldpwd_heap;
	const char	*pwd_env;

	oldpwd_heap = getcwd(NULL, 0);
	if (oldpwd_heap)
		return (oldpwd_heap);
	pwd_env = env_get_value(env, "PWD");
	if (!pwd_env)
		return (NULL);
	return (ft_strdup(pwd_env));
}

int	cd_to_home(t_env **penv, char *oldpwd_heap)
{
	const char	*home;

	home = env_get_value(*penv, "HOME");
	if (!home || home[0] == '\0')
	{
		if (oldpwd_heap)
			free(oldpwd_heap);
		return (cd_err("HOME not set"));
	}
	return (cd_chdir_and_update(penv, home, oldpwd_heap));
}

int	cd_to_oldpwd(t_env **penv, char *oldpwd_heap)
{
	const char	*oldpwd_env;

	oldpwd_env = env_get_value(*penv, "OLDPWD");
	if (!oldpwd_env || oldpwd_env[0] == '\0')
	{
		if (oldpwd_heap)
			free(oldpwd_heap);
		return (cd_err("OLDPWD not set"));
	}
	ft_putendl_fd((char *)oldpwd_env, STDOUT_FILENO);
	return (cd_chdir_and_update(penv, oldpwd_env, oldpwd_heap));
}
