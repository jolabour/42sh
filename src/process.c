/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 07:47:49 by jolabour          #+#    #+#             */
/*   Updated: 2018/09/06 03:31:26 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			process(t_42sh *sh)
{
	prompt(sh->env, sh);
	if (get_line(sh) != 1)
		return ;
	ft_putstr(sh->input);
	/*ft_putnbr(sh->size_of_window);
	ft_putnbr(sh->line_pos + sh->prompt_len);
	ft_putnbr(sh->len_line);*/
}
