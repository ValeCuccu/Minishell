/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapt_redirs_apply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 00:00:00 by anpastac          #+#    #+#             */
/*   Updated: 2026/01/21 00:00:00 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <errno.h>
#include <unistd.h>

int	ap_apply_redirs(t_redir *lst)
{
	t_redir	*r;

	r = lst;
	while (r != NULL)
	{
		if (ap_apply_one_redir(r) < 0)
			return (-1);
		r = r->next;
	}
	return (0);
}
