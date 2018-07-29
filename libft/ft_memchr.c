/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 06:44:36 by jolabour          #+#    #+#             */
/*   Updated: 2017/11/20 06:48:00 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void const *s, int c, size_t n)
{
	int				i;
	unsigned char	*str;
	unsigned char	car;

	car = (unsigned char)c;
	str = (unsigned char *)s;
	i = 0;
	while (n > 0)
	{
		if (str[i] == car)
			return (str + i);
		i++;
		n--;
	}
	return (NULL);
}
