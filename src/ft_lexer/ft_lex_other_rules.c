/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex_other_rules.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 07:03:05 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 21:35:28 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_lex_newline(t_lex *lex, t_42sh *shell)
{
	if (lex->input[lex->index] == '\n')
	{
		if (ft_lex_delimiter(lex, shell))
			return (0);
		ft_add_toklist(lex, NEWLINE);
		lex->alias_recognition = true;
		lex->current->start = lex->index;
		lex->current->len = 1;
		lex->index++;
		return (0);
	}
	return (1);
}

int			ft_lex_ionumber(t_lex *lex, t_42sh *shell)
{
	size_t	i;

	(void)shell;
	if ((lex->input[lex->index] == '>' || lex->input[lex->index] == '<')
		&& lex->current && lex->current->token == WORD
		&& lex->current->len <= 10
		&& lex->index == lex->current->start + lex->current->len)
	{
		i = lex->current->start;
		while (i < lex->current->start + lex->current->len)
		{
			if (lex->input[i] < '0' || lex->input[i] > '9')
				return (1);
			i++;
		}
		if (lex->current->len == 10 && ft_strncmp(lex->input
			+ lex->current->start, "2147483647", 10) > 0)
			return (1);
		lex->current->token = IO_NUMBER;
	}
	return (1);
}

int			ft_lex_blank(t_lex *lex, t_42sh *shell)
{
	if (lex->input[lex->index] == ' ' || lex->input[lex->index] == '\t')
	{
		if (ft_lex_delimiter(lex, shell))
			return (0);
		if (ft_match_alias_lock(lex->lock, lex->index))
			lex->alias_recognition = true;
		lex->index++;
		return (0);
	}
	return (1);
}

int			ft_lex_sharp(t_lex *lex, t_42sh *shell)
{
	(void)shell;
	if (lex->input[lex->index] == '#' && (!(lex->current)
		|| lex->index != lex->current->start + lex->current->len))
	{
		while (lex->input[lex->index] && lex->input[lex->index] != '\n')
			lex->index++;
		return (0);
	}
	return (1);
}

int			ft_lex_word(t_lex *lex, t_42sh *shell)
{
	(void)shell;
	if (!lex->current || lex->current->token != WORD
		|| lex->index != lex->current->start + lex->current->len)
	{
		ft_add_toklist(lex, WORD);
		lex->current->start = lex->index;
	}
	lex->current->len++;
	lex->index++;
	return (0);
}
