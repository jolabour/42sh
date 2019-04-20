/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex_quoting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 06:51:08 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/20 04:04:41 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_lex_backslash(t_lex *lex, t_42sh *shell)
{
	if (lex->input[lex->index] == '\\')
	{
		if (lex->input[lex->index + 1] == '\0'
			|| lex->input[lex->index + 1] == '\n')
		{
			lex->input[lex->index] = '\0';
			if (ft_lex_continue_line(lex, shell, "") != 1)
				return (-1);
		}
		else
		{
			ft_lex_word(lex, shell);
			ft_lex_word(lex, shell);
		}
		return (0);
	}
	return (1);
}

int			ft_lex_quote(t_lex *lex, t_42sh *shell)
{
	if (lex->input[lex->index] == '\'')
	{
		ft_lex_word(lex, shell);
		while (lex->input[lex->index] != '\'')
		{
			if (lex->input[lex->index] == '\0')
			{
				if (ft_lex_continue_line(lex, shell, "\'") != 1)
					return (-1);
			}
			else
				ft_lex_word(lex, shell);
		}
		ft_lex_word(lex, shell);
		return (0);
	}
	return (1);
}

int			ft_lex_dquote_mode(t_lex *lex, t_42sh *shell)
{
	int		i;
	int		ret;

	while (lex->input[lex->index] != '\"')
	{
		if (lex->input[lex->index] == '\0')
		{
			if (ft_lex_continue_line(lex, shell, "\"") != 1)
				return (-1);
		}
		else
		{
			i = 0;
			while (g_tokcond[i].dquote_mode == 0
					|| (ret = g_tokcond[i].cond(lex, shell)) > 0)
				i++;
			if (ret == -1)
				return (-1);
		}
	}
	return (0);
}

int			ft_lex_dquote(t_lex *lex, t_42sh *shell)
{
	if (lex->input[lex->index] == '\"')
	{
		ft_lex_word(lex, shell);
		if (ft_lex_dquote_mode(lex, shell))
			return (-1);
		ft_lex_word(lex, shell);
		return (0);
	}
	return (1);
}
