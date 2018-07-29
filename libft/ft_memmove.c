/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 02:05:27 by jolabour          #+#    #+#             */
/*   Updated: 2017/11/12 07:05:38 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void const *src, size_t n)
{
	unsigned char		*des;
	unsigned char		*sr;
	int					i;
	int					nb;

	sr = (unsigned char *)src;
	nb = (int)n;
	i = 0;
	des = (unsigned char *)dest;
	if (sr >= des)
		while (i < nb)
		{
			des[i] = sr[i];
			i++;
		}
	else
		while (nb > 0)
		{
			des[nb - 1] = sr[nb - 1];
			nb--;
		}
	return (dest);
}
