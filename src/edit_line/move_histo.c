/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_histo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 01:10:46 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/17 05:47:27 by jolabour         ###   ########.fr       */
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
	//pos_line = get_curent_line(sh);
	sh->stdin->nb_line = (sh->prompt_len + sh->stdin->len_line) / (sh->winsize);
	//tputs(tgoto(tgetstr("sc", NULL), 0, 0), 0, putchar_custom);
	while (i < sh->stdin->nb_line)
	{
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 0, putchar_custom);
		i++;
	}
	tputs(tgoto(tgetstr("ch", NULL), sh->prompt_len, sh->prompt_len), 0, putchar_custom);
	//tputs(tgetstr("cd", NULL), 0, putchar_custom);
	//ft_putstr_fd(sh->stdin->input, 0);
	//while (sh->stdin->line_pos > 0)
	//	move_to_left(sh);
	//tputs(tgoto(tgetstr("rc", NULL), 0, 0), 0, putchar_custom);
}

void			up_histo(t_42sh *sh)
{
	sh->winsize = get_winsize();
	if  (sh->history_mark->cur->next != NULL)
	{
		sh->history_mark->cur = sh->history_mark->cur->next;
		sh->history_mark->pos++;
		if ((int)ft_strlen(sh->history_mark->cur->str) >= sh->stdin->size_of_input - 10)
			up_input(sh);
		ft_strcpy(sh->stdin->input, sh->history_mark->cur->str);
		sh->stdin->input[ft_strlen(sh->history_mark->cur->str)] = '\0';
		sh->stdin->len_line = ft_strlen(sh->stdin->input);
		//sh->stdin->cursor_pos = sh->prompt_len + ft_strlen(sh->history_mark->cur->str);
		//sh->stdin->line_pos = ft_strlen(sh->history_mark->cur->str);
		clean_print_histo(sh);
		//line = (sh->prompt_len + sh->stdin->len_line) / (sh->winsize);
		//	tputs(tgoto(tgetstr("up", NULL), 1, 0), 1, putchar_custom);
	}
}

void			down_histo(t_42sh *sh)
{
	sh->winsize = get_winsize();
	if  (sh->history_mark->cur->prev != NULL)
	{
		sh->history_mark->cur = sh->history_mark->cur->prev;
		sh->history_mark->pos--;
		if ((int)ft_strlen(sh->history_mark->cur->str) >= sh->stdin->size_of_input - 10)
			up_input(sh);
		ft_strcpy(sh->stdin->input, sh->history_mark->cur->str);
		sh->stdin->input[ft_strlen(sh->history_mark->cur->str)] = '\0';
		sh->stdin->len_line = ft_strlen(sh->stdin->input);
		//if ((sh->prompt_len + sh->stdin->len_line) / (sh->winsize) > 0)
		//	tputs(tgoto(tgetstr("up", NULL), 1, 0), 1, putchar_custom);
		//sh->stdin->cursor_pos = sh->prompt_len + ft_strlen(sh->history_mark->cur->str);
		//sh->stdin->line_pos = ft_strlen(sh->history_mark->cur->str);
		clean_print_histo(sh);
		//	tputs(tgoto(tgetstr("up", NULL), 1, 0), 1, putchar_custom);
	}
}
