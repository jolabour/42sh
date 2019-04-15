/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_parse_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:45:30 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/16 01:34:57 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		ft_parse_sub_mode(char *word, size_t *index, char *quote)
{
	if (*quote != '\'' && word[*index] == '\\')
		(*index)++;
	else if (*quote != '\'' && word[*index] == '\"')
		*quote = *quote ? 0 : '\"';
	else if (*quote != '\"' && word[*index] == '\'')
		*quote = *quote ? 0 : '\'';
}

int			ft_parse_brace_var(char *word, size_t *index, t_txtlist **current)
{
	int		braces;
	char	quote;

	(*current)->token = BRACE_VAR;
	(*index)++;
	braces = 1;
	quote = 0;
	while (braces)
	{
		ft_parse_sub_mode(word, index, &quote);
		if (!quote && word[*index] == '{')
			braces++;
		else if (!quote && word[*index] == '}')
			braces--;
		(*index)++;
	}
	return (0);
}

int			ft_parse_par_var(char *word, size_t *index, t_txtlist **current)
{
	int		pars;
	char	quote;

	(*index)++;
	pars = 1;
	(*current)->token = word[*index] == '(' ? ARTH_EXPR : CMD_SUB;
	quote = 0;
	while (pars)
	{
		ft_parse_sub_mode(word, index, &quote);
		if (!quote && word[*index] == '(')
			pars++;
		else if (!quote && word[*index] == ')' && word[(*index) + 1] == ')'
			&& (*current)->token == ARTH_EXPR && pars == 2)
		{
			(*index) += 2;
			return (0);
		}
		else if (!quote && word[*index] == ')')
			pars--;
		(*index)++;
	}
	(*current)->token = CMD_SUB;
	return (0);
}

int			ft_parse_var(char *word, size_t *index,
			t_txtlist **current, bool *dquote)
{
	int		ret;

	if (word[*index] == '$')
	{
		ret = 0;
		ft_add_txtlist(word, VAR, current, *dquote);
		(*current)->start = *index;
		(*current)->dquote = *dquote;
		(*index)++;
		if (ft_get_spparam(word[*index]))
			(*index)++;
		else if (ft_isalpha(word[*index]) || word[*index] == '_')
			while (ft_isalnum(word[*index]) || word[*index] == '_')
				(*index)++;
		else if (word[*index] == '{')
			ret = ft_parse_brace_var(word, index, current);
		else if (word[*index] == '(')
			ret = ft_parse_par_var(word, index, current);
		(*current)->len = *index - (*current)->start;
		return (ret);
	}
	return (1);
}

int			ft_parse_bquote(char *word, size_t *index,
			t_txtlist **current, bool *dquote)
{
	char	quote;

	quote = 0;
	if (word[*index] == '`')
	{
		ft_add_txtlist(word, CMD_SUB_BQUOTE, current, *dquote);
		(*current)->start = *index;
		(*index)++;
		while (!quote && word[*index] != '`')
		{
			ft_parse_sub_mode(word, index, &quote);
			(*index)++;
		}
		(*index)++;
		(*current)->len = *index - (*current)->start;
		return (0);
	}
	return (1);
}
