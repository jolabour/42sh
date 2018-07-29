/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 02:04:33 by jolabour          #+#    #+#             */
/*   Updated: 2017/11/20 07:32:31 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_begin(char const *s)
{
	size_t		i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	return (i);
}

static size_t	ft_end(char const *s)
{
	size_t		i;

	i = ft_strlen(s) - 1;
	while (i > 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i--;
	return (ft_strlen(s) - i - 1);
}

char			*ft_strtrim(char const *s)
{
	if (!s)
		return (NULL);
	if (ft_begin(s) == ft_strlen(s))
		return (ft_strdup(""));
	return (ft_strsub(s, ft_begin(s), ft_strlen(s) - ft_end(s) - ft_begin(s)));
}
