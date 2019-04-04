/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 19:35:47 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/04 03:15:14 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int					check_input_select(t_42sh *sh, long buf)
{
	int				i;
	const long		input_tab_select[7] = {RIGHT_KEY,
	LEFT_KEY, DEL, OPT_C, OPT_X, CTRL_C, CTRL_D};
	const t_ak		action_tab_select[7] =
	{move_to_right_select,
	move_to_left_select, del_select, copy_select,
	cut_select, ctrlc_action, ctrld_action};

	i = 0;
	while (i < 7)
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
