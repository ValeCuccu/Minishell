/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonio <student.42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2025/10/28 00:00:00 by antonio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

/*
** bi_unset:
**
** Comportamento:
**   unset VAR1 VAR2 VAR3 ...
**
** Per ogni argomento:
**   - se il nome non è valido come identificatore di env:
**        minishell: unset: 'VAR?': not a valid identifier
**     e setta err = 1
**
**   - se il nome è valido:
**        lo rimuove dall'env chiamando env_unset_key()
**
** Return:
**   0 se tutto ok
**   1 se almeno un nome era invalido
*/
int	bi_unset(char **av, t_env **penv)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	while (av[i])
	{
		if (!ap_is_valid_env_key(av[i]))
		{
			ap_err_msg_quoted("unset", av[i], "not a valid identifier");
			err = 1;
		}
		else
			env_unset_key(penv, av[i]);
		i++;
	}
	return (err);
}
