/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 00:26:26 by jolabour          #+#    #+#             */
/*   Updated: 2018/08/04 06:04:38 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		add_char(char *input, t_42sh *sh)
{
	char	tmp[256];

	if (sh->line_pos != sh->len_line)
	{
		ft_strcpy(tmp, &sh->input[sh->line_pos]);
		sh->input[sh->line_pos] = input[0];
		ft_strcpy(sh->input + sh->line_pos + 1, tmp);
	}
	else
		sh->input[sh->line_pos] = input[0];
	sh->line_pos++;
	sh->len_line++;
}

void		delete_char(t_42sh *sh)
{
	char tmp[256];

	if (sh->line_pos != sh->len_line)
	{
		ft_strcpy(tmp, &sh->input[sh->line_pos]);
		sh->input[sh->line_pos] = '\0';
		ft_strcpy(sh->input + sh->line_pos - 1, tmp);
	}
	else
		sh->input[sh->line_pos - 1] = '\0';
	sh->line_pos--;
	sh->len_line--;
}

void		delete_input(t_42sh *sh)
{
	if (sh->line_pos > 0)
	{
		delete_char(sh);
		tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
		tputs(tgetstr("dc", NULL), 1, putchar_custom);
	}
}
