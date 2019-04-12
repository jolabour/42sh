/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:40:38 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/12 03:01:44 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void				up_input(t_42sh *sh)
{
	char			*tmp;

	tmp = ft_strdup(sh->stdin->input);
	ft_strdel(&sh->stdin->input);
	sh->stdin->size_of_input = sh->stdin->size_of_input * 2;
	sh->stdin->input = (char*)ft_malloc_exit(
		sizeof(char) * sh->stdin->size_of_input);
	ft_strcpy(sh->stdin->input, tmp);
	ft_strdel(&tmp);
}

void				add_one(t_42sh *sh, long buf)
{
	if (!ft_isprint((int)buf))
		return ;
	if (sh->stdin->len_line >= sh->stdin->size_of_input - 10)
		up_input(sh);
	sh->winsize = get_winsize();
	add_char(buf, sh);
	sh->stdin->len_line++;
	free(sh->history_mark->cur->str);
	sh->history_mark->cur->str = ft_strdup(sh->stdin->input);
	move_to_right(sh);
	clean_print(sh);
}

int					check_input(t_42sh *sh, long buf)
{
	const long		input_tab[NB_INPUT] = {RIGHT_KEY, LEFT_KEY, DEL, CTRL_C,
		CTRL_D, HOME, END, OPT_B, OPT_F, OPT_C, OPT_X, OPT_V, OPT_UP,
		OPT_DOWN, UP_KEY, DOWN_KEY, CTRL_R};
	const t_ak		action_tab[NB_INPUT] = {move_to_right, move_to_left,
		delete_input_buf, ctrlc_action, ctrld_action, move_to_start,
		move_to_end, move_to_begin_word, move_to_end_word, select_mode,
		select_mode, ft_paste, move_up, move_down,
		up_histo, down_histo, ctrlr_action};
	int				i;

	i = -1;
	while (++i < NB_INPUT)
	{
		if (input_tab[i] == buf)
		{
			action_tab[i](sh);
			if (i == 3)
				return (-1);
			if (i == 4)
				return (-2);
			if (i == 9 || i == 10 || i == 11)
				return (2);
			return (1);
		}
	}
	add_one(sh, buf);
	return (0);
}
