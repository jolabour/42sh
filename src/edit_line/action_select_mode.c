/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_select_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 22:49:28 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/04 03:10:39 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void				copy_select(t_42sh *sh)
{
	if (sh->stdin->str_to_paste != NULL)
		ft_strdel(&sh->stdin->str_to_paste);
	if (sh->stdin->end_und > sh->stdin->start_und)
		sh->stdin->str_to_paste = ft_strsub(sh->stdin->input,
				sh->stdin->start_und,
				sh->stdin->end_und - sh->stdin->start_und + 1);
	else if (sh->stdin->end_und < sh->stdin->start_und)
		sh->stdin->str_to_paste = ft_strsub(sh->stdin->input,
				sh->stdin->end_und,
				sh->stdin->start_und - sh->stdin->end_und + 1);
	else if (sh->stdin->end_und == sh->stdin->start_und)
		sh->stdin->str_to_paste = ft_strsub(sh->stdin->input,
				sh->stdin->start_und, 1);
}

void				del_select(t_42sh *sh)
{
	int		tmp2;
	char	*tmp;

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
		if (sh->stdin->end_und == sh->stdin->len_line)
			tmp = ft_strdup(sh->stdin->input + sh->stdin->end_und);
		else		
			tmp = ft_strdup(sh->stdin->input + sh->stdin->end_und + 1);
		ft_strcpy(sh->stdin->input + sh->stdin->start_und, tmp);
		free(tmp);
	}
	sh->stdin->len_line = ft_strlen(sh->stdin->input);
}

void				cut_select(t_42sh *sh)
{
	copy_select(sh);
	del_select(sh);
}
