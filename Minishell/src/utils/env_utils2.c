/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:19:09 by vacuccu           #+#    #+#             */
/*   Updated: 2025/10/27 16:19:28 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	same_key(const char *a, const char *b)
{
	size_t	len;

	if (!a || !b)
		return (0);
	len = ft_strlen(a);
	if (len != ft_strlen(b))
		return (0);
	return (ft_strncmp(a, b, len) == 0);
}
