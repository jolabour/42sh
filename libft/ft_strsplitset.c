/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 04:30:58 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/12/05 17:54:59 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_word_len(const char *s, char const *delims)
{
	const char	*start;

	start = s;
	while (!ft_strchr(delims, *s))
		++s;
	return (s - start);
}

static int		ft_word_count(const char *s, char const *delims)
{
	int		words;

	words = 0;
	while (*s)
	{
		if (!ft_strchr(delims, *s) && (ft_strchr(delims, s[1]) || s[1] == 0))
			++words;
		++s;
	}
	return (words);
}

static void		free_split(char **tab, int last)
{
	while (last-- > 0)
		free(tab[last]);
	free(tab);
}

char			**ft_strsplitset(char const *s, char const *delims)
{
	char		**split;
	char const	*start;
	int			i;
	int			words;

	if (!s || !(split = (char **)malloc(sizeof(*split)
					* ((words = ft_word_count(s, delims)) + 1))))
		return (NULL);
	start = s;
	split[words] = NULL;
	i = 0;
	while (i < words)
	{
		while (ft_strchr(delims, *s))
			++s;
		if (!(split[i++] = ft_strsub(start, s - start, ft_word_len(s, delims))))
		{
			free_split(split, i);
			return (NULL);
		}
		while (!ft_strchr(delims, *s))
			++s;
	}
	return (split);
}
