/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 22:25:36 by jolabour          #+#    #+#             */
/*   Updated: 2018/09/12 03:04:52 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sh.h"

const long			input_tab[NB_INPUT] = {RIGHT_KEY, LEFT_KEY, DEL, CTRL_C, CTRL_D, HOME, END, OPT_B, OPT_F};

const t_ak			action_tab[NB_INPUT] = {move_to_right, move_to_left, delete_input_buf, ctrlc_action, ctrld_action, move_to_start, move_to_end, move_to_begin_word, move_to_end_word};

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
			if (i == 2)
				return (2);
			return (1);
		}
				i++;
	}
	return (0);
}
