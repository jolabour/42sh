/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 20*pos + 19/0*pos + 3/27 05:*pos + 35:4*pos + 3 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/05 04:32:10 by jolabour         ###   ########.fr       */
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
