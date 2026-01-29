/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2026/01/21 15:07:41 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	handler_heredoc(int signo)
{
	(void)signo;
	ms_sig_set(SIGINT);
}

static void	handler_interactive(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	vc_set_last_status(130);
}

void	setup_signals_interactive(void)
{
	ms_sig_clear();
	signal(SIGINT, handler_interactive);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_signals_heredoc(void)
{
	struct sigaction	sa;

	ms_sig_clear();
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handler_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
