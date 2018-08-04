/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 03:56:06 by jolabour          #+#    #+#             */
/*   Updated: 2018/08/04 04:03:49 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		insert_mode_on(void)
{
	tputs(tgetstr("im", NULL), 1, putchar_custom);
}

void		insert_mode_off(void)
{
	tputs(tgetstr("ei", NULL), 1, putchar_custom);
}
