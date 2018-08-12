/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 00:54:28 by jolabour          #+#    #+#             */
/*   Updated: 2018/08/13 00:41:38 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void				move_to_right_select(t_42sh *sh, int pos)
{
	if (sh->line_pos < sh->len_line)
	{
		tputs(tgetstr("mr", NULL), 1, putchar_custom);
		if (pos <= sh->line_pos)
			ft_putstr("\x1b[38;5;196m");
		else
			ft_putstr("\033[0m");
		delete_input(sh);
		ft_putchar_fd(sh->input[sh->line_pos], 0);
		ft_putstr("\033[0m");
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
			ft_putstr("\x1b[38;5;196m");
		else
			ft_putstr("\033[0m");
		delete_input(sh);
		ft_putchar_fd(sh->input[sh->line_pos], 0);
		sh->line_pos++;
		move_to_left(sh);
		move_to_left(sh);
		ft_putstr("\033[0m");
		tputs(tgetstr("me", NULL), 1, putchar_custom);
	}
}

void				exit_right(t_42sh *sh)
{
	ft_putstr("\033[0m");
	delete_input(sh);
	ft_putchar_fd(sh->input[sh->line_pos], 0);
	sh->line_pos++;
}

void				exit_left(t_42sh *sh)
{
	ft_putstr("\033[0m");
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

void				copy_select(t_42sh *sh, int pos)
{
	if (sh->str_to_paste != NULL)
		ft_strdel(&sh->str_to_paste);
	if (sh->line_pos > pos)
		sh->str_to_paste = ft_strsub(sh->input, pos, sh->line_pos);
	else if (sh->line_pos < pos)
		sh->str_to_paste = ft_strsub(sh->input, sh->line_pos, pos - sh->line_pos);
	else
		return ;
}

void				cut_select(t_42sh *sh, int pos)
{
	int				tmp;

	copy_select(sh, pos);
	while (sh->line_pos > pos)
		delete_input_buf(sh);
	if (sh->line_pos < pos)
	{
		tmp = sh->line_pos;
		while (sh->line_pos < pos)
			move_to_right(sh);
		while (tmp < pos)
		{
			delete_input_buf(sh);
			tmp++;;
		}
	}
}

void				select_mode(t_42sh *sh)
{
	int				i;
	unsigned char	buf[7];
	int				pos;

	pos = sh->line_pos;
	while (42)
	{
		if ((i = read(0, buf, 6)) > 0)
		{
			if (buf[0] == 27 && buf[2] == 'C')
				move_to_right_select(sh, pos);
			else if (buf[0] == 27 && buf[2] == 'D')
				move_to_left_select(sh, pos);
			else if (buf[0] == 195)
			{
				copy_select(sh, pos);
				exit_select_mode(sh, pos);
				return ;
			}
			else if (buf[0] == 226)
			{
				cut_select(sh, pos);
			//	exit_select_mode(sh, pos);
				return ;
			}
			else
			{
				exit_select_mode(sh, pos);
				return ;
			}
		}
	}
}

