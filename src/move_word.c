/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 01:44:48 by jolabour          #+#    #+#             */
/*   Updated: 2018/11/18 01:01:11 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		move_to_begin_word(t_42sh *sh)
{
	if ((sh->stdin->line_pos == sh->stdin->len_line
				&& sh->input[sh->stdin->line_pos - 1] == ' ')
					|| (sh->input[sh->stdin->line_pos] != ' '
						&& sh->input[sh->stdin->line_pos - 1] == ' '))
		move_to_left(sh);
	while (sh->stdin->line_pos > 0 && sh->input[sh->stdin->line_pos] == ' ')
		move_to_left(sh);
	while (sh->stdin->line_pos > 0 && sh->input[sh->stdin->line_pos - 1] != ' ')
		move_to_left(sh);
}

void		move_to_end_word(t_42sh *sh)
{
	if (sh->input[sh->stdin->line_pos] != ' ' && sh->input[sh->stdin->line_pos + 1] == ' ')
		move_to_right(sh);
	while (sh->stdin->line_pos < sh->stdin->len_line && sh->input[sh->stdin->line_pos] == ' ')
		move_to_right(sh);
	while (sh->stdin->line_pos < sh->stdin->len_line && sh->input[sh->stdin->line_pos + 1] != ' ')
		move_to_right(sh);
}
