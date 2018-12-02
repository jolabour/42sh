/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_select_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 22:49:28 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/02 22:49:20 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void				copy_select(t_42sh *sh)
{
	if (sh->stdin->str_to_paste != NULL)
		ft_strdel(&sh->stdin->str_to_paste);
	if (sh->stdin->end_und > sh->stdin->start_und)
		sh->stdin->str_to_paste = ft_strsub(sh->input, sh->stdin->start_und, sh->stdin->end_und - sh->stdin->start_und + 1);
	else if (sh->stdin->end_und < sh->stdin->start_und)
		sh->stdin->str_to_paste = ft_strsub(sh->input, sh->stdin->end_und, sh->stdin->start_und - sh->stdin->end_und + 1);
	else if (sh->stdin->end_und == sh->stdin->start_und)
		sh->stdin->str_to_paste = ft_strsub(sh->input, sh->stdin->start_und, 1);
}

void				del_select(t_42sh *sh)
{
	int		tmp2;
	char	tmp[256];

	tmp2 = 0;
	if (sh->stdin->start_und > sh->stdin->end_und)
	{
		tmp2 = sh->stdin->start_und;
		sh->stdin->start_und = sh->stdin->end_und;
		sh->stdin->end_und = tmp2;
	}
	while (sh->stdin->start_und <= sh->stdin->end_und)
	{
		ft_strcpy(tmp, &sh->input[sh->stdin->start_und]);
		ft_strcpy(sh->input + sh->stdin->start_und - 1, tmp);
		sh->input[sh->stdin->len_line - 1] = '\0';
		sh->stdin->start_und++;
	}


	/*int				tmp;

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
	  }*/
}

void				cut_select(t_42sh *sh)
{
	copy_select(sh);
	del_select(sh);
}
