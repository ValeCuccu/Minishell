/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:04:40 by vacuccu           #+#    #+#             */
/*   Updated: 2025/01/17 16:03:22 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	*copy_w(const char *s, int start_w, int end_w)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(end_w - start_w + 1);
	if (!word)
		return (NULL);
	while (start_w < end_w)
		word[i++] = s[start_w++];
	word[i] = '\0';
	return (word);
}

static void	fclean(char **arr, int j)
{
	if (!arr)
	{
		while (--j >= 0)
			free(arr[j]);
		free(arr);
	}
	return ;
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		start_w;
	int		j;

	i = 0;
	j = 0;
	arr = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			start_w = i;
			while (s[i] != '\0' && s[i] != c)
				i++;
			arr[j++] = copy_w(s, start_w, i);
			fclean(arr, j);
		}
	}
	arr[j] = NULL;
	return (arr);
}
