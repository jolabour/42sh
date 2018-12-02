/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 22:25:36 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/02 21:51:12 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sh.h"

const long			input_tab[NB_INPUT] = {RIGHT_KEY, LEFT_KEY, DEL, CTRL_C, CTRL_D, HOME, END, OPT_B, OPT_F, OPT_C, OPT_X, OPT_V};

const t_ak			action_tab[NB_INPUT] = {move_to_right, move_to_left, delete_input_buf, ctrlc_action, ctrld_action, move_to_start, move_to_end, move_to_begin_word, move_to_end_word, select_mode, select_mode, ft_paste};

int					check_input(t_42sh *sh, long buf)
{
	int			i;

	i = 0;
	while (i < NB_INPUT)
	{
		if (input_tab[i] == buf)
		{
			action_tab[i](sh);
			if (i == 3)
				return (-1);
			if (i != 9 && i != 10)
				return (2);
			return (1);
		}
		i++;
	}
	sh->winsize = get_winsize();
	add_char(buf, sh);
	sh->stdin->len_line++;
	move_to_right(sh);
	clean_print(sh);
	return (0);
}
