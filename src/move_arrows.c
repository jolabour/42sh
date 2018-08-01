/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_arrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 17:07:05 by jolabour          #+#    #+#             */
/*   Updated: 2018/08/01 20:22:36 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		putchar_custom(int c)
{
	write(0, &c, 1);
	return (0);
}

void		move_to_right(t_42sh *sh)
{
	if (sh->line_pos < (int)ft_strlen(sh->input))
	{
		tputs(tgoto(tgetstr("nd", NULL), 1, 0), 1, putchar_custom);
		sh->line_pos++;
	}
}


void		move_to_left(t_42sh *sh)
{
	if (sh->line_pos > 0)
	{
		tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
		sh->line_pos--;
	}
}
