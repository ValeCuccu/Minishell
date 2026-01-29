/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2026/01/21 10:11:26 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "../.././includes/minishell.h"

int	bi_exit_child(char **av, t_env **penv)
{
	int	code;

	(void)penv;
	if (!av[1])
		return (get_last_status());
	if (!ms_try_parse_exit(av[1], &code))
		return (2);
	if (av[2])
		return (1);
	return (code);
}
