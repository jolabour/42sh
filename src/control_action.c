/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:09:06 by jolabour          #+#    #+#             */
/*   Updated: 2018/09/06 01:36:02 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ctrlc_action(t_42sh *sh)
{
	ft_putchar('\n');
	sh->input[0] = '\0';
}

void			ctrld_action(t_42sh *sh)
{
	(void)sh;
	insert_mode_off();
	exit(0);
}

void			paste(t_42sh *sh)
{
	if (sh->str_to_paste != NULL)
		ft_paste(sh);
}
