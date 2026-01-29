/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2025/10/29 16:32:31 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

/*
** bi_env:
**   Stampa l'ambiente in formato KEY=VAL
**   per ogni variabile definita.
**
** Return:
**   0 sempre.
*/
int	bi_env(t_env *env)
{
	while (env)
	{
		if (env->key)
		{
			ft_putstr_fd(env->key, 1);
			ft_putstr_fd("=", 1);
			if (env->val)
				ft_putstr_fd(env->val, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	return (0);
}
