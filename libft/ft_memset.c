/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 07:17:01 by jolabour          #+#    #+#             */
/*   Updated: 2017/11/10 07:31:37 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	void			*s1;
	unsigned char	*str;

	i = 0;
	str = s;
	s1 = str;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s1);
}
