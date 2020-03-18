/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 06:54:33 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/26 06:24:25 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_lex_sub_mode(t_lex *lex, t_42sh *shell, char *quote)
{
	if (*quote != '\"' && lex->input[lex->index] == '\'')
		*quote = *quote ? 0 : '\'';
	else if (*quote != '\'' && lex->input[lex->index] == '\"')
		*quote = *quote ? 0 : '\"';
	if (*quote != '\'' && lex->input[lex->index] == '\\')
		return (ft_lex_backslash(lex, shell));
	else
		return (ft_lex_word(lex, shell));
}

int			ft_lex_dollar_brace(t_lex *lex, t_42sh *shell)
{
	int		braces;
	char	quote;

	braces = 1;
	quote = 0;
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
			if (!quote && lex->input[lex->index] == '{')
				braces++;
			if (!quote && lex->input[lex->index] == '}')
				braces--;
			if (ft_lex_sub_mode(lex, shell, &quote))
				return (-1);
		}
	}
	return (0);
}

int			ft_lex_dollar_par(t_lex *lex, t_42sh *shell)
{
	int		pars;
	char	quote;

	pars = 1;
	quote = 0;
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
			if (!quote && lex->input[lex->index] == '(')
				pars++;
			if (!quote && lex->input[lex->index] == ')')
				pars--;
			if (ft_lex_sub_mode(lex, shell, &quote))
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
