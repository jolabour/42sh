/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:09:06 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/12 03:09:56 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ctrlc_action(t_42sh *sh)
{
	reset_term(sh);
	ft_putchar('\n');
	sh->stdin->input[0] = '\0';
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
