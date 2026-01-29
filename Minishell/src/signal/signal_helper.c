/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2026/01/22 18:35:00 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t	g_ap_sig = 0;

void	ms_sig_set(int signo)
{
	g_ap_sig = (sig_atomic_t)signo;
}

int	ms_sig_get(void)
{
	return ((int)g_ap_sig);
}

void	ms_sig_clear(void)
{
	g_ap_sig = 0;
}
