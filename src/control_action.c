/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:09:06 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/05 17:47:14 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ctrlc_action(t_42sh *sh)
{
	ft_putchar('\n');
	sh->stdin->input[0] = '\0';
	sh->stdin->ctrlc = 1;
}

void			ctrld_action(t_42sh *sh)
{
	(void)sh;
	exit(0);
}

void			paste(t_42sh *sh)
{
	if (sh->stdin->str_to_paste != NULL)
		ft_paste(sh);
}
