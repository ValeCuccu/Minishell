/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:35:59 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/21 12:08:45 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

int	status_store(int op, int value)
{
	static int	saved = 0;

	if (op == 1)
		saved = value;
	return (saved);
}

int	get_last_status(void)
{
	return (status_store(0, 0));
}

void	vc_set_last_status(int value)
{
	(void)status_store(1, value);
}

int	exit_req_store(int op, int value)
{
	static int	req = 0;

	if (op == 1)
		req = value;
	return (req);
}

int	exit_code_store(int op, int value)
{
	static int	code = 0;

	if (op == 1)
		code = value;
	return (code);
}
