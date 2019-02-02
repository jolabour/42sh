/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_arrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 17:07:05 by jolabour          #+#    #+#             */
/*   Updated: 2019/01/25 02:36:18 by ttresori         ###   ########.fr       */
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
	int		i;

	i = get_curent_line(sh);
	sh->winsize = get_winsize();
	if (i == 0)
	{
		tputs(tgoto(tgetstr("ch", NULL), sh->prompt_len, sh->prompt_len), 0, putchar_custom);
		sh->stdin->line_pos = 0;
		sh->stdin->cursor_pos = sh->prompt_len;
	}
	else
	{
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, putchar_custom);
		sh->stdin->line_pos = ((i * sh->winsize)) - sh->prompt_len;
		sh->stdin->cursor_pos = (i * sh->winsize);
	}
}

void		move_to_end(t_42sh *sh)
{
	int		i;

	sh->winsize = get_winsize();
	i = get_curent_line(sh);
	sh->stdin->nb_line = (sh->prompt_len + sh->stdin->len_line) / (sh->winsize);
	if (i == sh->stdin->nb_line)
	{
		tputs(tgoto(tgetstr("ch", NULL), (sh->stdin->len_line + sh->prompt_len) - (i * sh->winsize), (sh->stdin->len_line + sh->prompt_len) - (i * sh->winsize)), 0, putchar_custom);
		sh->stdin->line_pos = sh->stdin->len_line;
		sh->stdin->cursor_pos = sh->prompt_len + sh->stdin->len_line;
	}
	else
	{
		tputs(tgoto(tgetstr("ch", NULL), sh->winsize - 1, sh->winsize - 1), 0, putchar_custom);
		sh->stdin->line_pos = (((i + 1) * sh->winsize)) - sh->prompt_len - 1;
		sh->stdin->cursor_pos = ((i + 1)* sh->winsize) - 1;
	}
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