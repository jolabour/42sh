/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 01:20:30 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/23 08:03:41 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void				before_print(t_42sh *sh, int pos_line)
{
	int				i;

	i = 0;
	while (i < pos_line)
	{
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 0, putchar_custom);
		i++;
	}
	tputs(tgoto(tgetstr("ch", NULL), sh->prompt_len, sh->prompt_len),
			0, putchar_custom);
}

void				clean_print_select(t_42sh *sh)
{
	int			i;
	int			pos_line;

	pos_line = get_curent_line(sh);
	sh->stdin->nb_line = (sh->prompt_len + sh->stdin->len_line) / (sh->winsize);
	tputs(tgoto(tgetstr("sc", NULL), 0, 0), 0, putchar_custom);
	before_print(sh, pos_line);
	tputs(tgetstr("cd", NULL), 0, putchar_custom);
	i = 0;
	while (sh->stdin->input[i] != '\0')
	{
		if ((i == sh->stdin->start_und && sh->stdin->start_und
					<= sh->stdin->end_und) || (i == sh->stdin->end_und
						&& sh->stdin->end_und <= sh->stdin->start_und))
			tputs(tgetstr("mr", NULL), 1, putchar_custom);
		ft_putchar_fd(sh->stdin->input[i], 0);
		if ((i == sh->stdin->start_und && sh->stdin->start_und
					> sh->stdin->end_und) || (i == sh->stdin->end_und
						&& sh->stdin->end_und > sh->stdin->start_und)
				|| (sh->stdin->start_und == sh->stdin->end_und))
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
				return ;
			}
		}
	}
}
