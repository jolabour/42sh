/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 21:32:59 by jolabour          #+#    #+#             */
/*   Updated: 2019/01/19 21:55:12 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		builtin_echo(t_42sh *sh)
{
	int		i;

	i = 1;
	while (sh->argv->argv[i])
	{
		ft_putstr(sh->argv->argv[i]);
		if (sh->argv->argv[i + 1] != NULL)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}
