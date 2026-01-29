/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:30:00 by anpastac          #+#    #+#             */
/*   Updated: 2026/01/22 20:54:11 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

void	free_everything(t_env *env)
{
	ms_close_extra_fds();
	clear_history();
	if (env)
		free_env_list(env);
}

int	is_blank_line(const char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i] && is_space(s[i]))
		i++;
	return (s[i] == '\0');
}

void	run_one_command_line(char *one, t_env **penv)
{
	t_cmd	*cmds;
	int		parse_status;
	int		st;

	if (!one)
		return ;
	if (isatty(STDIN_FILENO) && one[0] != '\0')
		add_history(one);
	if (is_blank_line(one))
		return ;
	parse_status = 0;
	cmds = parse_input(one, *penv, &parse_status);
	if (!cmds)
	{
		vc_set_last_status(parse_status);
		return ;
	}
	st = ap_execute_line(cmds, penv);
	(void)st;
	free_cmd_list(cmds);
}

int	has_newline(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	chomp_newline(char *s)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
}
