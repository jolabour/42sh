/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 08:40:37 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/12 08:44:36 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			check_reverse(t_42sh *sh, int *i)
{
	if (sh->argv->size > 2)
	{
		if (ft_strequ(sh->argv->argv[*i + 1], "!") == 1)
		{
			sh->argv->size--;
			*i = *i + 1;
			return (1);
		}
	}
	return (0);
}

void		check_reverse_end(int reverse, t_42sh *sh)
{
	if (reverse == 1)
	{
		sh->argv->size++;
		if (sh->retval == 0)
		{
			sh->retval = 1;
			return ;
		}
		sh->retval = 0;
	}
}
