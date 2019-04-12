/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 08:21:50 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/12 08:23:37 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		print_error_alias(char *str, t_42sh *sh, int mode)
{
	if (mode == 1)
	{
		ft_putstr_fd("42sh: alias: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": not found", 2);
		sh->retval = 1;
	}
	else
	{
		ft_putstr_fd("42sh: alias: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" : invalid alias name", 2);
		sh->retval = 1;
	}
}
