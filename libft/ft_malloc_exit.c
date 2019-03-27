/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 00:05:27 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/27 00:06:23 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_putulglg_fd(unsigned long long nbr, int fd)
{
	if (nbr >= 10)
		ft_putulglg_fd(nbr / 10, fd);
	ft_putchar_fd(nbr % 10 + '0', fd);
}

void			*ft_malloc_exit(size_t size)
{
	void		*addr;

	if ((addr = malloc(size)))
		return (addr);
	ft_putstr_fd("42sh: malloc: cannot allocate ", 2);
	ft_putulglg_fd(size, 2);
	ft_putstr_fd(" bytes\n", 2);
	exit(2);
}
