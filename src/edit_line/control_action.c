/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:09:06 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/10 11:33:04 by jolabour         ###   ########.fr       */
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
	reset_term(sh);
}

void			paste(t_42sh *sh)
{
	if (sh->stdin->str_to_paste != NULL)
		ft_paste(sh);
}
