/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 00:54:28 by jolabour          #+#    #+#             */
/*   Updated: 2018/08/10 04:22:53 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void				move_to_right_select(t_42sh *sh, int pos)
{
	if (sh->line_pos < sh->len_line)
	{
		tputs(tgetstr("mr", NULL), 1, putchar_custom);
		if (pos >= 0)
			ft_putstr("\x1b[38;5;196m");
		delete_input(sh);
		ft_putchar_fd(sh->input[sh->line_pos], 0);
		ft_putstr("\033[22;37m");
		tputs(tgetstr("me", NULL), 1, putchar_custom);
		sh->line_pos++;
	}
}

void				move_to_left_select(t_42sh *sh, int pos)
{
	if (sh->line_pos - 1 > 0 && sh->line_pos == sh->len_line)
	{
		move_to_left(sh);
		return ;
	}
	if (sh->line_pos > 0)
	{
		tputs(tgetstr("mr", NULL), 1, putchar_custom);
		if (pos <= 0)
			ft_putstr("\x1b[38;5;196m");
		delete_input(sh);
		ft_putchar_fd(sh->input[sh->line_pos], 0);
		sh->line_pos++;
		move_to_left(sh);
		move_to_left(sh);
		ft_putstr("\033[22;37m");
		tputs(tgetstr("me", NULL), 1, putchar_custom);
	}
}


void				select_mode(t_42sh *sh)
{
	int				i;
	unsigned char	buf[7];
	int				pos;

	pos = 0;
	while (42)
	{
		if ((i = read(0, buf, 6)) > 0)
		{
			buf[i] = '\0';
			if (buf[0] == 27 && buf[2] == 'C')
			{
				move_to_right_select(sh, pos);
				pos++;
			}
			else if (buf[0] == 27 && buf[2] == 'D')
			{
				move_to_left_select(sh, pos);
				pos--;
			}
			//move_to_left_select(sh);
			/*else if (OPT_C)
				;*/
			/*else if (OPT_X)
				;
			*/else
				return ;
		}
	}
}

