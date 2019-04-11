/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 02:46:10 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/11 05:41:00 by jolabour         ###   ########.fr       */
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

	words = 1;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == 0))
			++words;
		++s;
	}
	return (words);
}

char			**ft_strsplit_path(char const *s, char c)
{
	char		**split;
	size_t		i;
	size_t		j;
	size_t		words;

	if (s)
	{
		split = (char **)ft_malloc_exit(sizeof(*split)
					* ((words = ft_word_count(s, c)) + 1));
		split[words] = NULL;
		i = 0;
		j = 0;
		while (j < words - 1)
		{
			while (s[i] && s[i] == c)
				++i;
			split[j++] = ft_strsub(s, i, ft_word_len(s + i, c));
			while (s[i] && s[i] != c)
				++i;
		}
		split[j] = ft_strdup("./");
		return (split);
	}
	split = ft_malloc_exit(sizeof(char*) * 2);
	split[0] = ft_strdup("./");
	split[1] = NULL;
	return (split);
}
