/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_suwxz.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 04:57:27 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/27 04:57:29 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		test_s(t_42sh *sh, struct stat info)
{
	if ((int)info.st_size == 0)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_u(t_42sh *sh, struct stat info)
{
	if (S_ISUID & info.st_mode)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_w(t_42sh *sh, struct stat info)
{
	if (S_IWUSR & info.st_mode)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_x(t_42sh *sh, struct stat info)
{
	if (S_IXUSR & info.st_mode)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_z(t_42sh *sh, struct stat info)
{
	(void)info;
	if (sh->argv->argv[2])
		sh->retval = 0;
	else
		sh->retval = 1;
}
