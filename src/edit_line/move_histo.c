/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_histo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 01:10:46 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/23 10:32:37 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			clean_print_histo(t_42sh *sh)
{
	int			i;

	i = 0;
	while (sh->stdin->line_pos > 0)
		move_to_left(sh);
	tputs(tgetstr("cd", NULL), 0, putchar_custom);
	ft_putstr_fd(sh->stdin->input, 0);
	sh->stdin->nb_line = (sh->prompt_len + sh->stdin->len_line) / (sh->winsize);
	while (i < sh->stdin->nb_line)
	{
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 0, putchar_custom);
		i++;
	}
	tputs(tgoto(tgetstr("ch", NULL), sh->prompt_len, sh->prompt_len),
			0, putchar_custom);
	while (sh->stdin->line_pos < sh->stdin->len_line)
		move_to_right(sh);
}

void			up_histo(t_42sh *sh)
{
	sh->winsize = get_winsize();
	if (sh->history_mark->cur->next != NULL)
	{
		sh->history_mark->cur = sh->history_mark->cur->next;
		sh->history_mark->pos++;
		while ((int)ft_strlen(sh->history_mark->cur->str)
			>= sh->stdin->size_of_input - 10)
			up_input(sh);
		ft_strcpy(sh->stdin->input, sh->history_mark->cur->str);
		sh->stdin->input[ft_strlen(sh->history_mark->cur->str)] = '\0';
		ft_move_cursor_left(sh->stdin->cursor_pos, sh->prompt_len);
		tputs(tgetstr("cd", NULL), 0, putchar_custom);
		sh->stdin->len_line = ft_strlen(sh->stdin->input);
		ft_putstr_fd(sh->stdin->input, 0);
		if ((sh->stdin->len_line + sh->prompt_len) % sh->winsize == 0)
			ft_putstr_fd("\n", 0);
		sh->stdin->line_pos = sh->stdin->len_line;
		sh->stdin->cursor_pos = sh->stdin->line_pos + sh->prompt_len;
	}
}

void			down_histo(t_42sh *sh)
{
	sh->winsize = get_winsize();
	if (sh->history_mark->cur->prev != NULL)
	{
		sh->history_mark->cur = sh->history_mark->cur->prev;
		sh->history_mark->pos--;
		while ((int)ft_strlen(sh->history_mark->cur->str)
			>= sh->stdin->size_of_input - 10)
			up_input(sh);
		ft_strcpy(sh->stdin->input, sh->history_mark->cur->str);
		sh->stdin->input[ft_strlen(sh->history_mark->cur->str)] = '\0';
		ft_move_cursor_left(sh->stdin->cursor_pos, sh->prompt_len);
		tputs(tgetstr("cd", NULL), 0, putchar_custom);
		sh->stdin->len_line = ft_strlen(sh->stdin->input);
		ft_putstr_fd(sh->stdin->input, 0);
		if ((sh->stdin->len_line + sh->prompt_len) % sh->winsize == 0)
			ft_putstr_fd("\n", 0);
		sh->stdin->line_pos = sh->stdin->len_line;
		sh->stdin->cursor_pos = sh->stdin->line_pos + sh->prompt_len;
	}
}
