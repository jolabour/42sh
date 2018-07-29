/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 02:33:07 by jolabour          #+#    #+#             */
/*   Updated: 2017/11/10 06:53:36 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char const *str, char const *to_find)
{
	int i;
	int j;
	int size;

	i = 0;
	size = ft_strlen(to_find);
	j = 0;
	if (size == 0)
		return ((char *)str);
	while (str[i] != '\0')
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
