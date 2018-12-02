/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_select_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 22:44:43 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/02 21:46:38 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void				move_to_right_select(t_42sh *sh)
{
	if (sh->stdin->line_pos < sh->stdin->len_line)
	{
		move_to_right(sh);
		sh->stdin->end_und++;
	}
	clean_print_select(sh);
}

void				move_to_left_select(t_42sh *sh)
{
	if (sh->stdin->line_pos > 0)
	{
		move_to_left(sh);
		sh->stdin->end_und--;
	}
	clean_print_select(sh);
}
