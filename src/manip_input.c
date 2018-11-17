/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 00:26:26 by jolabour          #+#    #+#             */
/*   Updated: 2018/09/12 02:16:42 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		add_char(long input, t_42sh *sh)
{
	char	tmp[256];

	if (sh->line_pos != sh->len_line)
	{
		ft_strcpy(tmp, &sh->input[sh->line_pos]);
		sh->input[sh->line_pos] = (char)input;
		ft_strcpy(sh->input + sh->line_pos + 1, tmp);
		sh->input[sh->len_line + 1] = '\0';
	}
	else
	{
		sh->input[sh->len_line] = (char)input;
		sh->input[sh->len_line + 1] = '\0';
	}
	sh->len_line++;
}

void		delete_char(t_42sh *sh)
{
	char tmp[256];

	if (sh->line_pos != sh->len_line)
	{
		ft_strcpy(tmp, &sh->input[sh->line_pos]);
		ft_strcpy(sh->input + sh->line_pos - 1, tmp);
		sh->input[sh->len_line - 1] = '\0';
	}
	else
		sh->input[sh->len_line - 1] = '\0';
	sh->len_line--;

}

void		delete_cut(t_42sh *sh)
{
	if (sh->line_pos > 0)
	{
		delete_char(sh);
		tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
		tputs(tgetstr("dc", NULL), 1, putchar_custom);
	}
}

void		delete_input_buf(t_42sh *sh)
{
	if (sh->line_pos > 0)
	{
		delete_char(sh);
		move_to_left(sh);
		tputs(tgetstr("dc", NULL), 1, putchar_custom);
	}
}

void		delete_after_cursor(t_42sh *sh)
{
	while (sh->line_pos < sh->len_line)
		move_to_right(sh);
	while (sh->line_pos > 0)
	{
		if (sh->line_pos > 0)
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
	if (sh->line_pos >= 0)
		tputs(tgetstr("dc", NULL), 1, putchar_custom);
}
