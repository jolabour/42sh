/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 01:34:06 by jolabour          #+#    #+#             */
/*   Updated: 2017/11/14 01:34:11 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*tab;
	size_t	i;

	i = 0;
	tab = NULL;
	if (!(tab = malloc(sizeof(void) * size)))
		return (NULL);
	while (i < size)
	{
		tab[i] = '\0';
		i++;
	}
	return (tab);
}
