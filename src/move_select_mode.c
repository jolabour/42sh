/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_select_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 22:44:43 by jolabour          #+#    #+#             */
/*   Updated: 2018/08/13 22:46:35 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void				move_to_right_select(t_42sh *sh, int pos)
{
	if (sh->line_pos < sh->len_line)
	{
		tputs(tgetstr("mr", NULL), 1, putchar_custom);
		if (pos <= sh->line_pos)
			ft_putstr(SET_FG_RED);
		else
			ft_putstr(RESET_COLOR);
		delete_input(sh);
		ft_putchar_fd(sh->input[sh->line_pos], 0);
		ft_putstr(RESET_COLOR);
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
		if (pos >= sh->line_pos)
			ft_putstr(SET_FG_RED);
		else
			ft_putstr(RESET_COLOR);
		delete_input(sh);
		ft_putchar_fd(sh->input[sh->line_pos], 0);
		sh->line_pos++;
		move_to_left(sh);
		move_to_left(sh);
		ft_putstr(RESET_COLOR);
		tputs(tgetstr("me", NULL), 1, putchar_custom);
	}
}
