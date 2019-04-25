/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_glprs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 04:57:20 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/25 02:23:48 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		test_g(t_42sh *sh, struct stat info)
{
	if (S_ISGID & info.st_mode)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_l(t_42sh *sh, struct stat info)
{
	if ((S_ISLNK(info.st_mode)) == 1)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_p(t_42sh *sh, struct stat info)
{
	if ((S_ISFIFO(info.st_mode)) == 1)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_r(t_42sh *sh, struct stat info)
{
	if (S_IRUSR & info.st_mode)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_su(t_42sh *sh, struct stat info)
{
	if ((S_ISSOCK(info.st_mode)) == 1)
		sh->retval = 0;
	else
		sh->retval = 1;
}
