/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 19:35:47 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/05 17:49:43 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

const long			input_tab_select[NB_INPUT_SELECT] = {RIGHT_KEY, LEFT_KEY, DEL, OPT_C, OPT_X, CTRL_C, CTRL_D, CTRL_R};

const t_ak			action_tab_select[NB_INPUT_SELECT] = {move_to_right_select, move_to_left_select, del_select, copy_select, cut_select, ctrlc_action, ctrld_action, ctrlr_action};

int					check_input_select(t_42sh *sh, long buf)
{
	int			i;

	i = 0;
	while (i < NB_INPUT)
	{
		if (input_tab_select[i] == buf)
		{
			action_tab_select[i](sh);
			if (i == 0 || i == 1)
				return (2);
			if (i == 7)
				return (-1);
			return (1);
		}
		i++;
	}
	return (0);
}
