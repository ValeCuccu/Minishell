/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonio <student.42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 00:00:00 by antonio           #+#    #+#             */
/*   Updated: 2025/10/28 00:00:00 by antonio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

/*
** bi_run_child:
**
** Esegue un builtin DENTRO IL FIGLIO (es. in una pipeline).
**
** Ritorna:
**   exit status del builtin
**
** Nota:
**   - cd / export / unset devono poter modificare l'env,
**     quindi gli passiamo penv.
**   - exit nel figlio non spegne tutta la shell, ma solo il figlio,
**     quindi qui va benissimo chiamare bi_exit(av) e tornare quel codice.
*/
int	bi_run_child(char **av, t_env **penv)
{
	int	status;

	status = 0;
	if (!av || !av[0])
		return (0);
	if (ft_strncmp(av[0], "cd", 3) == 0)
		status = bi_cd(av, penv);
	else if (ft_strncmp(av[0], "export", 7) == 0)
		status = bi_export(av, penv);
	else if (ft_strncmp(av[0], "unset", 6) == 0)
		status = bi_unset(av, penv);
	else if (ft_strncmp(av[0], "exit", 5) == 0)
		status = bi_exit_child(av, penv);
	else if (ft_strncmp(av[0], "echo", 5) == 0)
		status = bi_echo(av);
	else if (ft_strncmp(av[0], "pwd", 4) == 0)
		status = bi_pwd();
	else if (ft_strncmp(av[0], "env", 4) == 0)
		status = bi_env(*penv);
	return (status);
}
