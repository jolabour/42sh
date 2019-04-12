/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 08:29:01 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/12 08:29:36 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		test_equal(t_42sh *sh, int *pos)
{
	if (ft_strequ(sh->argv->argv[*pos + 1],
				sh->argv->argv[*pos + 3]) == *pos + 1)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_diff(t_42sh *sh, int *pos)
{
	if (ft_strequ(sh->argv->argv[*pos + 1],
				sh->argv->argv[*pos + 3]) == *pos + 1)
		sh->retval = 1;
	else
		sh->retval = 0;
}

void		test_eq(t_42sh *sh, int *pos)
{
	int		tmp;
	int		tmp2;

	tmp = ft_atoi(sh->argv->argv[*pos + 1]);
	tmp2 = ft_atoi(sh->argv->argv[*pos + 3]);
	if (tmp == tmp2)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_ne(t_42sh *sh, int *pos)
{
	int		tmp;
	int		tmp2;

	tmp = ft_atoi(sh->argv->argv[*pos + 1]);
	tmp2 = ft_atoi(sh->argv->argv[*pos + 3]);
	if (tmp != tmp2)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_ge(t_42sh *sh, int *pos)
{
	int		tmp;
	int		tmp2;

	tmp = ft_atoi(sh->argv->argv[*pos + 1]);
	tmp2 = ft_atoi(sh->argv->argv[*pos + 3]);
	if (tmp >= tmp2)
		sh->retval = 0;
	else
		sh->retval = 1;
}
