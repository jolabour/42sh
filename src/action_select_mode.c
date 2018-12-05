/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_select_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 22:49:28 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/05 17:47:02 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void				copy_select(t_42sh *sh)
{
	if (sh->stdin->str_to_paste != NULL)
		ft_strdel(&sh->stdin->str_to_paste);
	if (sh->stdin->end_und > sh->stdin->start_und)
		sh->stdin->str_to_paste = ft_strsub(sh->stdin->input, sh->stdin->start_und, sh->stdin->end_und - sh->stdin->start_und + 1);
	else if (sh->stdin->end_und < sh->stdin->start_und)
		sh->stdin->str_to_paste = ft_strsub(sh->stdin->input, sh->stdin->end_und, sh->stdin->start_und - sh->stdin->end_und + 1);
	else if (sh->stdin->end_und == sh->stdin->start_und)
		sh->stdin->str_to_paste = ft_strsub(sh->stdin->input, sh->stdin->start_und, 1);
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
	if ((sh->stdin->end_und - sh->stdin->start_und) == sh->stdin->len_line)
		sh->stdin->input[0] = '\0';
	else
	{
		ft_strcpy(tmp, sh->stdin->input + sh->stdin->end_und + 1);
		ft_strcpy(sh->stdin->input + sh->stdin->start_und, tmp);
	}
	sh->stdin->len_line = ft_strlen(sh->stdin->input);
}

void				cut_select(t_42sh *sh)
{
	copy_select(sh);
	del_select(sh);
}
