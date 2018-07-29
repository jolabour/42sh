/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 06:52:27 by jolabour          #+#    #+#             */
/*   Updated: 2017/11/10 07:15:40 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *str, char const *to_find, size_t n)
{
	size_t	i;
	int		j;
	int		size;

	i = 0;
	size = ft_strlen(to_find);
	j = 0;
	if (size == 0)
		return ((char *)str);
	while (str[i] && (size + i) <= n)
	{
		while (str[i + j] == to_find[j])
		{
			if (j == size - 1)
				return ((char *)str + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
