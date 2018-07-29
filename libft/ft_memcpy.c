/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 07:42:35 by jolabour          #+#    #+#             */
/*   Updated: 2017/11/20 07:07:40 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, void const *src, size_t n)
{
	size_t		i;
	char const	*sr;
	char		*des;

	i = 0;
	sr = (char *)src;
	des = (char *)dest;
	while (i < n)
	{
		des[i] = sr[i];
		i++;
	}
	return (dest);
}
