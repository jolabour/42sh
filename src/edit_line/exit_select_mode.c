/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_select_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 22:46:40 by jolabour          #+#    #+#             */
/*   Updated: 2018/08/17 01:11:45 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void				exit_right(t_42sh *sh)
{
	delete_input(sh);
	ft_putchar_fd(sh->input[sh->line_pos], 0);
	sh->line_pos++;
}

static void				exit_left(t_42sh *sh)
{
	delete_input(sh);
	ft_putchar_fd(sh->input[sh->line_pos], 0);
	sh->line_pos++;
	move_to_left(sh);
	move_to_left(sh);
}
void				exit_select_mode(t_42sh *sh, int pos)
{
	int			end_pos;

	end_pos = sh->line_pos;
	while (sh->line_pos > pos)
	{
		move_to_left_select(sh, pos);
		if (sh->line_pos == pos)
			exit_left(sh);
	}
	while (sh->line_pos < pos)
	{
		move_to_right_select(sh, pos);
		if (sh->line_pos == pos && pos < sh->len_line)
			exit_right(sh);
	}
	while (sh->line_pos < end_pos)
		move_to_right(sh);
	while (sh->line_pos > end_pos)
		move_to_left(sh);
/*	while (sh->line_pos > sh->len_line)
		move_to_left(sh);*/
}
