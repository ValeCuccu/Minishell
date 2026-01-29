/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:05:00 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/29 13:09:22 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include <unistd.h>

void	shell_loop(t_env **penv)
{
	char	*line;
	int		interactive;
	int		ret;

	interactive = isatty(STDIN_FILENO);
	if (!interactive)
	{
		ap_err_msg(NULL, "non-interactive input not supported");
		vc_set_last_status(2);
		return ;
	}
	while (1)
	{
		ret = read_and_prepare_line(&line, interactive);
		if (ret == 1)
			break ;
		if (ret == 2)
			continue ;
		if (exec_line_or_error(line, penv))
			break ;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	int		code;

	(void)ac;
	(void)av;
	env = init_env(envp);
	if (!env)
	{
		perror("minishell: env init");
		return (1);
	}
	vc_set_last_status(0);
	if (isatty(STDIN_FILENO))
		ms_disable_echoctl();
	shell_loop(&env);
	get_next_line(-1);
	if (ms_exit_requested())
		code = ms_get_exit_code();
	else
		code = get_last_status();
	free_everything(env);
	return (code);
}

int	read_and_prepare_line(char **line, int interactive)
{
	setup_signals_interactive();
	if (interactive)
		*line = readline("minishell$ ");
	else
		*line = get_next_line(STDIN_FILENO);
	if (!*line)
	{
		if (interactive)
			write(1, "exit\n", 5);
		return (1);
	}
	chomp_newline(*line);
	if (interactive)
		add_history(*line);
	if (is_blank_line(*line))
	{
		free(*line);
		return (2);
	}
	return (0);
}

int	exec_line_or_error(char *line, t_env **penv)
{
	if (!has_newline(line))
		run_one_command_line(line, penv);
	else
	{
		ap_err_msg(NULL, "multiline input not supported");
		vc_set_last_status(2);
	}
	if (ms_exit_requested())
	{
		free(line);
		get_next_line(-1);
		return (1);
	}
	free(line);
	return (0);
}
