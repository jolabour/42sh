/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 08:28:23 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/12 08:28:35 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		test_lt(t_42sh *sh, int *pos)
{
	int		tmp;
	int		tmp2;

	tmp = ft_atoi(sh->argv->argv[*pos + 1]);
	tmp2 = ft_atoi(sh->argv->argv[*pos + 3]);
	if (tmp < tmp2)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_le(t_42sh *sh, int *pos)
{
	int		tmp;
	int		tmp2;

	tmp = ft_atoi(sh->argv->argv[*pos + 1]);
	tmp2 = ft_atoi(sh->argv->argv[*pos + 3]);
	if (tmp <= tmp2)
		sh->retval = 0;
	else
		sh->retval = 1;
}
