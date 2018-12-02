/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_arrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 17:07:05 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/02 17:43:45 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		putchar_custom(int c)
{
	write(0, &c, 1);
	return (0);
}

void		move_to_right(t_42sh *sh)
{
	sh->winsize = get_winsize();
	if (sh->stdin->line_pos < sh->stdin->len_line)
	{
		if (sh->stdin->cursor_pos % sh->winsize == sh->winsize - 1)
		{
			tputs(tgoto(tgetstr("do", NULL), 1, 0), 1, putchar_custom);
			tputs(tgoto(tgetstr("cr", NULL), sh->winsize, sh->winsize), 1, putchar_custom);
		}
		else
			tputs(tgoto(tgetstr("nd", NULL), 1, 0), 1, putchar_custom);
		sh->stdin->line_pos++;
		sh->stdin->cursor_pos++;
	}
}

void		move_to_start(t_42sh *sh)
{
	while (sh->stdin->line_pos > 0)
		move_to_left(sh);
}

void		move_to_end(t_42sh *sh)
{
	while (sh->stdin->line_pos < sh->stdin->len_line)
		move_to_right(sh);
}

void		move_to_left(t_42sh *sh)
{
	if (sh->stdin->line_pos > 0)
	{
		if (sh->stdin->cursor_pos % sh->winsize == 0)
		{
			tputs(tgoto(tgetstr("up", NULL), 1, 0), 1, putchar_custom);
			tputs(tgoto(tgetstr("ch", NULL), sh->winsize - 1, sh->winsize - 1), 1, putchar_custom);
		}
		else
			tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
		sh->stdin->line_pos--;
		sh->stdin->cursor_pos--;
	}
}
