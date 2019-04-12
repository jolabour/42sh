/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_with.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 06:05:42 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/12 08:55:05 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_len(const char *s, char c)
{
	size_t		i;

	i = 1;
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
		while (*s != c && *s)
			++s;
		++words;
		while (*s == c && *s)
			++s;
	}
	return (words - 1);
}

char			**ft_strsplit_with(char const *s, char c)
{
	char		**split;
	size_t		i;
	size_t		j;
	size_t		words;

	if (!s || !(split = (char **)ft_malloc_exit(sizeof(*split)
					* ((words = ft_word_count(s, c)) + 1))))
		return (NULL);
	split[words] = NULL;
	i = 0;
	j = 0;
	while (j < words)
	{
		while (s[i] && s[i + 1] == c)
			i++;
		split[j++] = ft_strsub(s, i, ft_word_len(s + i, c));
		if (s[i])
			i++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (split);
}
