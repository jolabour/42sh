/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 07:00:36 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 07:01:47 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_find_operator(t_lex *lex)
{
	int		i;
	int		op;

	i = 0;
	op = -1;
	while (g_toktab[i].str)
	{
		while (g_toktab[i].str && !ft_strnequ(g_toktab[i].str,
			lex->input + lex->index, ft_strlen(g_toktab[i].str)))
			i++;
		if (g_toktab[i].str && (op == -1
			|| ft_strlen(g_toktab[i].str) > ft_strlen(g_toktab[op].str)))
			op = i;
		if (g_toktab[i].str)
			i++;
	}
	return (op);
}

int			ft_lex_operator(t_lex *lex, t_42sh *shell)
{
	int		op;

	op = ft_find_operator(lex);
	if (op >= 0)
	{
		if (ft_lex_delimiter(lex, shell))
			return (0);
		ft_add_toklist(lex, g_toktab[op].token);
		lex->current->start = lex->index;
		lex->current->len = ft_strlen(g_toktab[op].str);
		lex->index = lex->index + lex->current->len;
		if (g_toktab[op].redir_op)
			lex->redir_op = true;
		else if (g_toktab[op].alias_recognition)
			lex->alias_recognition = true;
		return (0);
	}
	return (1);
}
