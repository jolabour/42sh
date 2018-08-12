/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 02:50:13 by jolabour          #+#    #+#             */
/*   Updated: 2018/08/06 03:01:48 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		move_down(t_42sh *sh)
{
	int		co;

	co = tgetnum("co");
	if (sh->len_line <= co)
		return ;
	tputs(tgoto(tgetstr("do", NULL), 0, 1), 1, putchar_custom);
	sh->line_pos += co;
	while (sh->line_pos > sh->len_line)
	{
		tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
		sh->line_pos--;
	}
}
