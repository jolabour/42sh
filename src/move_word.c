/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 01:44:48 by jolabour          #+#    #+#             */
/*   Updated: 2018/08/12 20:13:20 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		move_to_begin_word(t_42sh *sh)
{
	if ((sh->line_pos == sh->len_line
				&& sh->input[sh->line_pos - 1] == ' ')
					|| (sh->input[sh->line_pos] != ' '
						&& sh->input[sh->line_pos - 1] == ' '))
		move_to_left(sh);
	while (sh->line_pos > 0 && sh->input[sh->line_pos] == ' ')
	{
		tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
		sh->line_pos--;
	}
	while (sh->line_pos > 0 && sh->input[sh->line_pos - 1] != ' ')
	{
		tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
		sh->line_pos--;
	}
}

void		move_to_end_word(t_42sh *sh)
{
	if (sh->input[sh->line_pos] != ' ' && sh->input[sh->line_pos + 1] == ' ')
		move_to_right(sh);
	while (sh->line_pos < sh->len_line && sh->input[sh->line_pos] == ' ')
	{
		tputs(tgoto(tgetstr("nd", NULL), 1, 0), 1, putchar_custom);
		sh->line_pos++;
	}
	while (sh->line_pos < sh->len_line && sh->input[sh->line_pos + 1] != ' ')
	{
		tputs(tgoto(tgetstr("nd", NULL), 1, 0), 1, putchar_custom);
		sh->line_pos++;
	}
}
