/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 00:26:26 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/17 03:58:11 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		add_char(long input, t_42sh *sh)
{
	char	tmp[256];

	if (sh->stdin->line_pos != sh->stdin->len_line)
	{
		ft_strcpy(tmp, &sh->stdin->input[sh->stdin->line_pos]);
		sh->stdin->input[sh->stdin->line_pos] = (char)input;
		ft_strcpy(sh->stdin->input + sh->stdin->line_pos + 1, tmp);
		sh->stdin->input[sh->stdin->len_line + 1] = '\0';
	}
	else
	{
		sh->stdin->input[sh->stdin->len_line] = (char)input;
		sh->stdin->input[sh->stdin->len_line + 1] = '\0';
	}
}

void		delete_char(t_42sh *sh)
{
	char tmp[256];

	if (sh->stdin->line_pos != sh->stdin->len_line)
	{
		ft_strcpy(tmp, &sh->stdin->input[sh->stdin->line_pos]);
		ft_strcpy(sh->stdin->input + sh->stdin->line_pos - 1, tmp);
		sh->stdin->input[sh->stdin->len_line - 1] = '\0';
	}
	else
		sh->stdin->input[sh->stdin->len_line - 1] = '\0';

}

void		delete_cut(t_42sh *sh)
{
	if (sh->stdin->line_pos > 0)
	{
		delete_char(sh);
		tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
		tputs(tgetstr("dc", NULL), 1, putchar_custom);
	}
}

void		delete(void)
{
	tputs(tgetstr("dc", NULL), 1, putchar_custom);
}

void		delete_input_buf(t_42sh *sh)
{
	sh->winsize = get_winsize();
	if (sh->stdin->len_line > 0 && sh->stdin->line_pos > 0)
	{
		delete_char(sh);
	/*	if (sh->stdin->cursor_pos % sh->winsize == 1)
		{
			tputs(tgoto(tgetstr("up", NULL), 1, 0), 1, putchar_custom);
			tputs(tgoto(tgetstr("ch", NULL), sh->winsize, sh->winsize), 1, putchar_custom);
		}
		else
			tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
		delete();
		if (sh->stdin->cursor_pos % sh->winsize == sh->winsize - 1)
		{
			tputs(tgoto(tgetstr("do", NULL), 1, 0), 1, putchar_custom);
			tputs(tgoto(tgetstr("cr", NULL), sh->winsize, sh->winsize), 1, putchar_custom);
		}
		else
			tputs(tgoto(tgetstr("nd", NULL), 1, 0), 1, putchar_custom);
		*/sh->stdin->len_line--;
		free(sh->history_mark->cur->str);
		sh->history_mark->cur->str = ft_strdup(sh->stdin->input);
		move_to_left(sh);
		clean_print(sh);
	}
/*	if (sh->stdin->cursor_pos != sh->stdin->len_line)
	{
		if ((sh->stdin->len_line + sh->prompt_len - 1) % sh->winsize == 0)
			sh->stdin->nb_line--;
	}
	else
	{
		if ((sh->stdin->len_line + sh->prompt_len + 1) % sh->winsize == 0)
			sh->stdin->nb_line--;
	}*/
}

void		delete_after_cursor(t_42sh *sh)
{
	while (sh->stdin->line_pos < sh->stdin->len_line)
		move_to_right(sh);
	while (sh->stdin->line_pos > 0)
	{
		if (sh->stdin->line_pos > 0)
			move_to_left(sh);
		delete_input(sh);
	}
	//ft_putnbr(sh->line_pos);
	/*int		cursor;

	cursor = sh->line_pos;
	while (sh->line_pos < sh->len_line)
		move_to_right(sh);
	while (sh->line_pos > cursor)
	{
		move_to_left(sh);
		delete_input(sh);
	}*/
}

void		delete_input(t_42sh *sh)
{
	if (sh->stdin->line_pos >= 0)
		tputs(tgetstr("dc", NULL), 1, putchar_custom);
}
