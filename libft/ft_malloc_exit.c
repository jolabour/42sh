/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 00:05:27 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/24 08:02:53 by geargenc         ###   ########.fr       */
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
	ft_putstr_fd("42sh: malloc: cannot allocate ", STDERR_FILENO);
	ft_putulglg_fd(size, STDERR_FILENO);
	ft_putstr_fd(" bytes\n", STDERR_FILENO);
	exit(2);
}
