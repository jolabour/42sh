/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex_bquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 06:57:53 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 06:58:06 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_lex_bquote_mode(t_lex *lex, t_42sh *shell)
{
	int		i;
	int		ret;

	while (lex->input[lex->index] != '`')
	{
		if (lex->input[lex->index] == '\0')
		{
			if (ft_lex_continue_line(lex, shell, "`") != 1)
				return (-1);
		}
		else
		{
			i = 0;
			while (g_tokcond[i].sub_mode == 0 ||
				(ret = g_tokcond[i].cond(lex, shell)) > 0)
				i++;
			if (ret == -1)
				return (-1);
		}
	}
	return (0);
}

int			ft_lex_bquote(t_lex *lex, t_42sh *shell)
{
	if (lex->input[lex->index] == '`')
	{
		ft_lex_word(lex, shell);
		if (ft_lex_bquote_mode(lex, shell))
			return (-1);
		ft_lex_word(lex, shell);
		return (0);
	}
	return (1);
}
