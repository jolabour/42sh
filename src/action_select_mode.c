/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_select_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 22:49:28 by jolabour          #+#    #+#             */
/*   Updated: 2018/08/13 22:59:09 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void				copy_select(t_42sh *sh, int pos)
{
	if (sh->str_to_paste != NULL)
		ft_strdel(&sh->str_to_paste);
	if (sh->line_pos > pos)
		sh->str_to_paste = ft_strsub(sh->input, pos, sh->line_pos + 1);
	else if (sh->line_pos < pos)
		sh->str_to_paste = ft_strsub(sh->input, sh->line_pos,
				pos - sh->line_pos + 1);
	else
		sh->str_to_paste = ft_strsub(sh->input, pos, 1);
}

void				del_select(t_42sh *sh, int pos)
{
	int				tmp;

	if (sh->line_pos == pos && pos != sh->len_line)
	{
		move_to_right(sh);
		delete_input_buf(sh);
	}
	if (sh->line_pos > pos && sh->line_pos < sh->len_line)
		move_to_right(sh);
	while (sh->line_pos > pos)
		delete_input_buf(sh);
	if (sh->line_pos < pos)
	{
		tmp = sh->line_pos;
		while (sh->line_pos < pos)
			move_to_right(sh);
		tputs(tgoto(tgetstr("nd", NULL), 1, 0), 1, putchar_custom);
		sh->line_pos++;
		sh->len_line++;
		while (tmp <= pos)
		{
			delete_input_buf(sh);
			tmp++;
		}
	}
}

void				cut_select(t_42sh *sh, int pos)
{
	copy_select(sh, pos);
	del_select(sh, pos);
}
