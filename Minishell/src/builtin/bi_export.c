/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by vale              #+#    #+#             */
/*   Updated: 2026/01/21 00:00:00 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

static int	ap_split_no_equal(const char *s, char **k, char **v)
{
	*k = ft_strdup(s);
	if (!*k)
		return (-1);
	*v = NULL;
	return (0);
}

static int	ap_split_with_equal(const char *s, char **k, char **v, char *eq)
{
	*k = ft_substr(s, 0, (size_t)(eq - s));
	if (!*k)
		return (-1);
	*v = ft_strdup(eq + 1);
	if (!*v)
	{
		free(*k);
		*k = NULL;
		return (-1);
	}
	return (0);
}

static int	ap_split_kv_assign(const char *s, char **k, char **v)
{
	char	*eq;

	*k = NULL;
	*v = NULL;
	eq = ft_strchr(s, '=');
	if (!eq)
		return (ap_split_no_equal(s, k, v));
	return (ap_split_with_equal(s, k, v, eq));
}

static int	ap_export_one(char *arg, t_env **penv)
{
	char	*k;
	char	*v;
	int		ret;

	if (ap_split_kv_assign(arg, &k, &v) == -1)
		return (1);
	if (!ap_is_valid_env_key(k))
	{
		ap_err_msg_quoted("export", k, "not a valid identifier");
		free(k);
		if (v)
			free(v);
		return (1);
	}
	if (v != NULL)
		ret = env_set_value(penv, k, v);
	else
		ret = env_set_value(penv, k, "");
	free(k);
	if (v)
		free(v);
	if (ret != 0)
		return (1);
	return (0);
}

int	bi_export(char **av, t_env **penv)
{
	int	i;
	int	err;

	if (!av || !av[0])
		return (0);
	if (!av[1])
		return (ms_export_print_all(*penv));
	i = 1;
	err = 0;
	while (av[i])
	{
		if (ap_export_one(av[i], penv))
			err = 1;
		i++;
	}
	return (err);
}
