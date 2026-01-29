/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapt_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2026/01/21 12:17:40 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"
#include <errno.h>

int	ap_cmd_count(t_cmd *head)
{
	int	n;

	n = 0;
	while (head != NULL)
	{
		n++;
		head = head->next;
	}
	return (n);
}

static int	ap_prepare_cmd_heredocs(t_cmd *c, t_ms_state *st)
{
	t_redir	*r;
	char	*tmp;

	r = c->redirs;
	while (r)
	{
		if (r->type == REDIR_HEREDOC)
		{
			tmp = NULL;
			if (heredoc_run(r, &tmp, st) < 0)
				return (-1);
			r->type = REDIR_IN;
			free(r->filename);
			r->filename = tmp;
		}
		r = r->next;
	}
	return (0);
}

int	ap_prepare_heredocs(t_cmd *head, t_env *env)
{
	t_cmd		*c;
	t_ms_state	st;

	if (!head)
		return (0);
	ft_bzero(&st, sizeof(st));
	st.env = env;
	st.head = head;
	st.hd_idx = 0;
	c = head;
	while (c)
	{
		if (ap_prepare_cmd_heredocs(c, &st) < 0)
			return (-1);
		c = c->next;
	}
	return (0);
}

static int	ap_run_by_count(t_cmd *line, t_env **penv, int n)
{
	if (n == 1)
		return (ap_run_single(line, penv));
	return (ap_run_pipeline(line, penv, n));
}

int	ap_execute_line(t_cmd *line, t_env **penv)
{
	int	n;
	int	st;

	if (!line)
		return (0);
	if (ap_prepare_heredocs(line, *penv) < 0)
	{
		if (errno == EINTR)
			vc_set_last_status(130);
		else
			vc_set_last_status(1);
		return (get_last_status());
	}
	n = ap_cmd_count(line);
	st = ap_run_by_count(line, penv, n);
	vc_set_last_status(st);
	return (st);
}
