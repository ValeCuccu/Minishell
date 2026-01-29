/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2025/10/29 17:10:39 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <sys/stat.h>
#include <unistd.h>

/*
** Ritorna 1 se la stringa contiene '/'.
** Esempi:
**  "ls"      -> 0
**  "./a.out" -> 1
**  "/bin/ls" -> 1
*/
static int	ap_has_slash(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

/*
** Ritorna 1 se p è una directory esistente, altrimenti 0.
*/
static int	ap_is_dir(const char *p)
{
	struct stat	st;

	if (stat(p, &st) == -1)
		return (0);
	if (S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

/*
** join di dir + "/" + cmd
** ritorna stringa allocata
*/
static char	*ap_join_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	return (res);
}

/*
** Cerca cmd nelle directory di PATH (dirs viene da ft_split(PATH, ':')).
** Se trova qualcosa di eseguibile e non directory, ritorna quel path allocato.
** Se non trova niente ritorna NULL.
*/
static char	*ap_search_in_path(const char *cmd, char **dirs)
{
	int		i;
	char	*full;

	i = 0;
	while (dirs[i])
	{
		full = ap_join_path(dirs[i], cmd);
		if (full && access(full, X_OK) == 0 && !ap_is_dir(full))
			return (full);
		if (full)
			free(full);
		i++;
	}
	return (NULL);
}

/*
** resolve_cmd_path:
**
** 1. Se cmd contiene '/', NON cerchiamo nel PATH. Usiamo cmd così com'è.
**    -> ritorno ft_strdup(cmd)
**
** 2. Altrimenti:
**    - prendiamo $PATH dall'env
**    - split ":" → dirs[]
**    - proviamo dirs[i] + "/" + cmd
**    - se troviamo qualcosa di eseguibile (e non directory), lo ritorniamo
**
** 3. Se non troviamo nulla → ritorniamo NULL.
**
** Ritorna: stringa allocata col path eseguibile, oppure NULL.
*/
char	*resolve_cmd_path(char *cmd, t_env *env)
{
	char	*path_val;
	char	**dirs;
	char	*full;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ap_has_slash(cmd))
		return (ft_strdup(cmd));
	path_val = env_get_value(env, "PATH");
	if (!path_val)
		return (NULL);
	dirs = ft_split(path_val, ':');
	if (!dirs)
		return (NULL);
	full = ap_search_in_path(cmd, dirs);
	ft_split_free(dirs);
	return (full);
}
