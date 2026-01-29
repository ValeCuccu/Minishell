/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_status2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:03:10 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/21 12:10:34 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

void	ms_request_exit(int code)
{
	exit_code_store(1, code);
	exit_req_store(1, 1);
}

int	ms_exit_requested(void)
{
	return (exit_req_store(0, 0));
}

int	ms_get_exit_code(void)
{
	return (exit_code_store(0, 0));
}
