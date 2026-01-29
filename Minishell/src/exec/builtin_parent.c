/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonio <student.42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 00:00:00 by antonio           #+#    #+#             */
/*   Updated: 2025/10/28 00:00:00 by antonio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

/*
** bi_run_parent:
**
** Esegue un builtin NEL PROCESSO PRINCIPALE della shell.
** Questo succede SOLO quando:
**   - hai un singolo comando
**   - ed è un builtin
**
** Perché serve il parent?
**   Perché builtins tipo cd / export / unset / exit
**   devono modificare lo stato della shell vera (env, cwd, uscita).
**
** Ritorna:
**   exit status del builtin
**
** Nota su exit:
**   Qui bi_exit(av) ti dà il codice con cui vuoi uscire.
**   Sarà responsabilità del chiamante decidere se fare davvero exit().
*/
int	bi_run_parent(char **av, t_env **penv)
{
	int	status;

	if (!av || !av[0])
		return (0);
	if (ft_strncmp(av[0], "cd", 3) == 0)
		return (bi_cd(av, penv));
	if (ft_strncmp(av[0], "export", 7) == 0)
		return (bi_export(av, penv));
	if (ft_strncmp(av[0], "unset", 6) == 0)
		return (bi_unset(av, penv));
	if (ft_strncmp(av[0], "exit", 5) == 0)
		return (bi_exit_parent(av, penv));
	if (ft_strncmp(av[0], "echo", 5) == 0)
		return (bi_echo(av));
	if (ft_strncmp(av[0], "pwd", 4) == 0)
		return (bi_pwd());
	if (ft_strncmp(av[0], "env", 4) == 0)
		return (bi_env(*penv));
	status = 0;
	return (status);
}
