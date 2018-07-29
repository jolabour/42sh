/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 08:00:44 by jolabour          #+#    #+#             */
/*   Updated: 2017/11/20 06:56:41 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, void const *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*sr;
	unsigned char	*des;

	i = 0;
	sr = (unsigned char *)src;
	des = (unsigned char *)dest;
	while (i < n)
	{
		des[i] = sr[i];
		if (sr[i] == (unsigned char)c)
			return (dest + i + 1);
		i++;
		if ((unsigned char)c == '\0' && sr[i] == '\0')
			return (dest + i + 1);
	}
	return (NULL);
}
