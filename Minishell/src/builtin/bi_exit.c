/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2026/01/21 09:05:43 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "../.././includes/minishell.h"

static void	exit_print_if_interactive(void)
{
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 1);
}

static int	exit_no_arg(void)
{
	int	st;

	st = get_last_status();
	ms_request_exit(st);
	return (st);
}

static int	exit_numeric_required(char *arg)
{
	ms_puterr3("minishell: exit: ", arg, ": numeric argument required");
	ms_request_exit(2);
	return (2);
}

static int	exit_too_many_args(void)
{
	ms_puterr3("minishell: exit: ", NULL, "too many arguments");
	return (1);
}

int	bi_exit_parent(char **av, t_env **penv)
{
	int	code;

	(void)penv;
	exit_print_if_interactive();
	if (!av[1])
		return (exit_no_arg());
	if (!ms_try_parse_exit(av[1], &code))
		return (exit_numeric_required(av[1]));
	if (av[2])
		return (exit_too_many_args());
	ms_request_exit(code);
	return (code);
}
