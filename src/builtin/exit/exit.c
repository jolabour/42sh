/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 03:50:31 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/09 02:46:09 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		builtin_exit(t_42sh *sh)
{
	int		i;

	if (sh->argv->size > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		sh->retval = 1;
		return ;
	}
	if (!sh->pgid)
		ft_putendl_fd("exit", 2);
	i = 0;
	if (sh->argv->size == 1)
		exit(sh->retval);
	while (sh->argv->argv[1][i])
	{
		if (ft_isdigit(sh->argv->argv[1][i]) == 0)
		{
			ft_putstr_fd("42sh: exit: ", 2);
			ft_putstr_fd(sh->argv->argv[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			sh->retval = 2;
			return ;
		}
		i++;
	}
	sh->retval = ft_atoi(sh->argv->argv[1]);
	exit(sh->retval);
}
