/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 05:30:18 by jolabour          #+#    #+#             */
/*   Updated: 2017/11/10 05:59:41 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	if (s[i] == '\0' && s[i] == c)
		return ((char *)s + i);
	i = 0;
	while (s[i])
	{
		if (count != 0 && s[i] == c)
			count--;
		if (count == 0 && s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
