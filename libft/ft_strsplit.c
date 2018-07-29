/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:46:59 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/04/21 19:56:29 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_word_len(const char *s, char c)
{
	size_t		i;

	i = 0;
	while (s[i] && s[i] != c)
		++i;
	return (i);
}

static	size_t	ft_word_count(const char *s, char c)
{
	size_t		words;

	words = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == 0))
			++words;
		++s;
	}
	return (words);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**split;
	size_t		i;
	size_t		j;
	size_t		words;

	if (!s || !(split = (char **)malloc(sizeof(*split)
					* ((words = ft_word_count(s, c)) + 1))))
		return (NULL);
	split[words] = NULL;
	i = 0;
	j = 0;
	while (j < words)
	{
		while (s[i] && s[i] == c)
			++i;
		split[j++] = ft_strsub(s, i, ft_word_len(s + i, c));
		while (s[i] && s[i] != c)
			++i;
	}
	return (split);
}
