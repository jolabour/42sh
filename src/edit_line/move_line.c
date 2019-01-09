/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 02:50:13 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/17 04:19:28 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		move_down(t_42sh *sh)
{
	int		i;

	i = get_curent_line(sh);
	sh->winsize = get_winsize();
	sh->stdin->nb_line = (sh->prompt_len + sh->stdin->len_line) / (sh->winsize);
	if (i == sh->stdin->nb_line)
		return ;
	else
	{
		i = 0;
		while (i < sh->winsize && sh->stdin->line_pos < sh->stdin->len_line)
		{
			move_to_right(sh);
			i++;
		}
	}
}

void		move_up(t_42sh *sh)
{
	int		i;

	sh->winsize = get_winsize();
	i = get_curent_line(sh);
	sh->stdin->nb_line = (sh->prompt_len + sh->stdin->len_line) / (sh->winsize);
	if (i == 0)
		return ;
	else
	{
		tputs(tgoto(tgetstr("up", NULL), sh->winsize - 1, sh->winsize - 1), 0, putchar_custom);
		sh->stdin->line_pos -= sh->winsize;
		sh->stdin->cursor_pos -= sh->winsize;
		while (sh->stdin->line_pos < 0)
			move_to_right(sh);
	}
}

