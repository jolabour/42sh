/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 05:35:43 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/27 05:37:11 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		test_lt(t_42sh *sh)
{
	int		tmp;
	int		tmp2;

	tmp = ft_atoi(sh->argv->argv[1]);
	tmp2 = ft_atoi(sh->argv->argv[3]);
	if (tmp < tmp2)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_le(t_42sh *sh)
{
	int		tmp;
	int		tmp2;

	tmp = ft_atoi(sh->argv->argv[1]);
	tmp2 = ft_atoi(sh->argv->argv[3]);
	if (tmp <= tmp2)
		sh->retval = 0;
	else
		sh->retval = 1;
}
