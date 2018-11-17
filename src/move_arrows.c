/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_arrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 17:07:05 by jolabour          #+#    #+#             */
/*   Updated: 2018/09/08 02:24:42 by jolabour         ###   ########.fr       */
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
	sh->size_of_window = get_winsize();
	if (sh->line_pos + sh->prompt_len == sh->size_of_window - 1)
	{
		tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, putchar_custom);
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, putchar_custom);
		sh->line_pos++;
	}
	else if (sh->line_pos < sh->len_line)
	{
		tputs(tgoto(tgetstr("nd", NULL), 1, 0), 1, putchar_custom);
		sh->line_pos++;
	}
}

void		move_to_start(t_42sh *sh)
{
	while (sh->line_pos > 0)
	{
		tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
		sh->line_pos--;
	}
}

void		move_to_end(t_42sh *sh)
{
	while (sh->line_pos < sh->len_line)
	{
		tputs(tgoto(tgetstr("nd", NULL), 1, 0), 1, putchar_custom);
		sh->line_pos++;
	}
}

void		move_to_left(t_42sh *sh)
{
	if (sh->line_pos > 0)
	{
		tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
		sh->line_pos--;
	}
}
