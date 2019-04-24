/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:09:06 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/24 07:54:08 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ctrlc_action(t_42sh *sh)
{
	reset_term(sh);
	while (sh->stdin->line_pos < sh->stdin->len_line)
		move_to_right(sh);
	ft_putstr_fd("\n", 0);
	sh->stdin->input[0] = '\0';
	sh->retval = 130;
	sh->stdin->ctrlc = 1;
}

void			ctrld_action(t_42sh *sh)
{
	(void)sh;
	if (ft_strlen(sh->stdin->input) > 0)
	{
		if (sh->stdin->line_pos != sh->stdin->len_line)
		{
			delete();
			sh->stdin->line_pos++;
			delete_char(sh);
			sh->stdin->line_pos--;
			sh->stdin->len_line--;
			clean_print(sh);
		}
	}
	else
	{
		reset_term(sh);
		sh->ctrld = 1;
	}
}

void			paste(t_42sh *sh)
{
	if (sh->stdin->str_to_paste != NULL)
		ft_paste(sh);
}
