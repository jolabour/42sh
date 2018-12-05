/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 00:54:28 by jolabour          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void				clean_print_select(t_42sh *sh)
{
	int			i;
	int			pos_line;

	i = 0;
	pos_line = get_curent_line(sh);
	sh->stdin->nb_line = (sh->prompt_len + sh->stdin->len_line) / (sh->winsize);
	tputs(tgoto(tgetstr("sc", NULL), 0, 0), 0, putchar_custom);
	while (i < pos_line)
	{
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 0, putchar_custom);
		i++;
	}
	tputs(tgoto(tgetstr("ch", NULL), sh->prompt_len, sh->prompt_len), 0, putchar_custom);
	tputs(tgetstr("cd", NULL), 0, putchar_custom);
	i = 0;
	while (sh->stdin->input[i] != '\0')
	{
		if ((i == sh->stdin->start_und && sh->stdin->start_und <= sh->stdin->end_und) || (i == sh->stdin->end_und && sh->stdin->end_und <= sh->stdin->start_und))
			tputs(tgetstr("mr", NULL), 1, putchar_custom);
		ft_putchar_fd(sh->stdin->input[i], 0);
		if ((i == sh->stdin->start_und && sh->stdin->start_und > sh->stdin->end_und) || (i == sh->stdin->end_und && sh->stdin->end_und > sh->stdin->start_und) || (sh->stdin->start_und == sh->stdin->end_und))
			tputs(tgetstr("me", NULL), 1, putchar_custom);
		i++;
	}
	tputs(tgoto(tgetstr("rc", NULL), 0, 0), 0, putchar_custom);
}

void				select_mode(t_42sh *sh)
{
	long			buf;
	int				i;

	sh->stdin->save_pos = sh->stdin->line_pos;
	sh->stdin->start_und = sh->stdin->line_pos;
	sh->stdin->end_und = sh->stdin->line_pos;
	while (42)
	{
		buf = 0;
		if ((i = read(0, &buf, 3)) > 0)
		{
			if ((i = check_input_select(sh, buf)) != 2)
			{
				if (i == -1)
					return ;
				clean_print(sh);
				while (sh->stdin->line_pos > sh->stdin->len_line)
					move_to_left(sh);
				return ;
			}
		}
	}
}
