/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 00:00:00 by anpastac          #+#    #+#             */
/*   Updated: 2026/01/21 00:00:00 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

static int	ms_env_count(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	ms_swap_env(t_env **a, t_env **b)
{
	t_env	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	ms_sort_env_array(t_env **arr, int n)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strncmp(arr[i]->key, arr[j]->key,
					ft_strlen(arr[i]->key) + 1) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	ms_export_print_one(t_env *node)
{
	ft_putstr_fd("declare -x ", 1);
	if (node->key)
		ft_putstr_fd(node->key, 1);
	if (node->val)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(node->val, 1);
		ft_putstr_fd("\"\n", 1);
	}
	else
		ft_putstr_fd("\n", 1);
}

int	ms_export_print_all(t_env *env)
{
	int		n;
	int		i;
	t_env	**arr;

	n = ms_env_count(env);
	if (n <= 0)
		return (0);
	arr = (t_env **)malloc(sizeof(t_env *) * n);
	if (!arr)
		return (1);
	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	ms_sort_env_array(arr, n);
	i = 0;
	while (i < n)
		ms_export_print_one(arr[i++]);
	free(arr);
	return (0);
}
