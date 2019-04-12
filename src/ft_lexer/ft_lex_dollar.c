/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 06:54:33 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 06:54:57 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_lex_sub_mode(t_lex *lex, t_42sh *shell)
{
	int		i;
	int		ret;

	i = 0;
	while (g_tokcond[i].sub_mode == 0
		|| (ret = g_tokcond[i].cond(lex, shell)) > 0)
		i++;
	return (ret);
}

int			ft_lex_dollar_brace(t_lex *lex, t_42sh *shell)
{
	int		braces;

	braces = 1;
	ft_lex_word(lex, shell);
	while (braces)
	{
		if (lex->input[lex->index] == '\0')
		{
			if (ft_lex_continue_line(lex, shell, "}") != 1)
				return (-1);
		}
		else
		{
			if (lex->input[lex->index] == '{')
				braces++;
			if (lex->input[lex->index] == '}')
				braces--;
			if (ft_lex_sub_mode(lex, shell))
				return (-1);
		}
	}
	return (0);
}

int			ft_lex_dollar_par(t_lex *lex, t_42sh *shell)
{
	int		pars;

	pars = 1;
	ft_lex_word(lex, shell);
	while (pars)
	{
		if (lex->input[lex->index] == '\0')
		{
			if (ft_lex_continue_line(lex, shell, ")") != 1)
				return (-1);
		}
		else
		{
			if (lex->input[lex->index] == '(')
				pars++;
			if (lex->input[lex->index] == ')')
				pars--;
			if (ft_lex_sub_mode(lex, shell))
				return (-1);
		}
	}
	return (0);
}

int			ft_lex_dollar(t_lex *lex, t_42sh *shell)
{
	if (lex->input[lex->index] == '$')
	{
		ft_lex_word(lex, shell);
		if (lex->input[lex->index] == '{')
			return (ft_lex_dollar_brace(lex, shell));
		if (lex->input[lex->index] == '(')
			return (ft_lex_dollar_par(lex, shell));
		if (ft_get_spparam(lex->input[lex->index]))
			ft_lex_word(lex, shell);
		return (0);
	}
	return (1);
}
