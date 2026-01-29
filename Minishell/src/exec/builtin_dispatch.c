/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2025/10/29 17:10:11 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

int	ap_is_builtin(const char *name)
{
	if (!name)
		return (0);
	if (ap_streq(name, "echo"))
		return (1);
	if (ap_streq(name, "pwd"))
		return (1);
	if (ap_streq(name, "env"))
		return (1);
	if (ap_streq(name, "cd"))
		return (1);
	if (ap_streq(name, "export"))
		return (1);
	if (ap_streq(name, "unset"))
		return (1);
	if (ap_streq(name, "exit"))
		return (1);
	return (0);
}

int	ap_is_parent_affecting_builtin(char **argv)
{
	if (!argv || !argv[0])
		return (0);
	if (ap_streq(argv[0], "cd"))
		return (1);
	if (ap_streq(argv[0], "export"))
		return (1);
	if (ap_streq(argv[0], "unset"))
		return (1);
	if (ap_streq(argv[0], "exit"))
		return (1);
	return (0);
}
