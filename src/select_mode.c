/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 00:54:28 by jolabour          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void				select_mode(t_42sh *sh)
{
	int				i;
	unsigned char	buf[7];
	int				pos;

	pos = sh->line_pos;
	while (42)
	{
		if ((i = read(0, buf, 6)) > 0)
		{
			buf[i] = '\0';
			if (RIGHT_KEY(buf))
				move_to_right_select(sh, pos);
			else if (LEFT_KEY(buf))
				move_to_left_select(sh, pos);
			else if (OPT_C(buf))
			{
				copy_select(sh, pos);
				exit_select_mode(sh, pos);
				return ;
			}
			else if (OPT_X(buf))
			{
				cut_select(sh, pos);
				return ;
			}
			else if (DEL(buf))
			{
				del_select(sh, pos);
				return ;
			}
			else
			{
				exit_select_mode(sh, pos);
				return ;
			}
		}
	}
}
