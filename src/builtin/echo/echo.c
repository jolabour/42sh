/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 21:32:59 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/09 04:17:31 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			check_opt_echo(t_42sh *sh)
{
	int		i;

	i = 1;
	if (sh->argv->argv[1][0] != '-')
		return (0);
	while (sh->argv->argv[1][i])
	{
		if (sh->argv->argv[1][i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void		builtin_echo(t_42sh *sh)
{
	int		i;
	int		n;

	i = 1;
	n = 0;
	if (write(1, NULL, 0) == -1)
	{
		ft_putendl_fd("42sh: echo: write error: Bad file descriptor", 2);
		sh->retval = 1;
		return ;
	}
	if (sh->argv->size > 1)
	{
		if ((n = check_opt_echo(sh)) == 1)
			i++;
		while (sh->argv->argv[i])
		{
			ft_putstr(sh->argv->argv[i]);
			if (sh->argv->argv[i + 1] != NULL)
				ft_putchar(' ');
			i++;
		}
	}
	if (n != 1)
		ft_putchar('\n');
	sh->retval = 0;
}
