/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:31:20 by vacuccu           #+#    #+#             */
/*   Updated: 2025/12/02 11:43:26 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

/* Un nome di variabile inizia con [A-Za-z_] e poi [A-Za-z0-9_]* */
int	is_var_start(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c == '_'))
		return (1);
	return (0);
}

int	is_var_char(char c)
{
	if (is_var_start(c) || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	get_var_end(const char *s, int pos)
{
	int	end;

	end = pos;
	while (s[end] && is_var_char(s[end]))
		end++;
	return (end);
}

char	*env_lookup(t_env *env, const char *name, int len)
{
	char	*var_name;
	char	*val;
	char	*out;

	var_name = substr_dup(name, 0, len);
	if (!var_name)
		return (NULL);
	val = get_env_value(env, var_name);
	if (!val)
		out = ft_strdup("");
	else
		out = ft_strdup(val);
	free(var_name);
	return (out);
}

/* ----------------------------- dequote_all -------------------------------- */
/* Rimuove SOLO i caratteri di quote ( ' e " ) di apertura/chiusura,
   copiando il contenuto così com’è.
   Se incontra quote non chiuse -> ritorna NULL (errore di sintassi). */

int	append_char(char **out, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	*out = join_and_free(*out, buf);
	return (*out != NULL);
}
