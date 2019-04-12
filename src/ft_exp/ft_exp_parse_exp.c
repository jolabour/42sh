/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_parse_exp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:45:30 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:53:21 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_parse_tilde(char *word, size_t *index,
			t_txtlist **current, bool *dquote)
{
	if (word[*index] == '~' && !(*dquote) && (*index == 0
		|| word[*index - 1] == ' ' || word[*index - 1] == '\n'
		|| word[*index - 1] == '\t' || word[*index - 1] == ':'))
	{
		ft_add_txtlist(word, TILDE, current, *dquote);
		(*current)->start = *index;
		(*index)++;
		if (word[*index] == '+' || word[*index] == '-')
			(*index)++;
		else if (ft_isalpha(word[*index]) || word[*index] == '_')
			while (ft_isalnum(word[*index]) || word[*index] == '_')
				(*index)++;
		(*current)->len = *index - (*current)->start;
		return (0);
	}
	return (1);
}

int			ft_parse_brace_var(char *word, size_t *index, t_txtlist **current)
{
	int		braces;

	(*current)->token = BRACE_VAR;
	(*index)++;
	braces = 1;
	while (braces)
	{
		if (word[*index] == '\0')
			return (-1);
		else if (word[*index] == '{')
			braces++;
		else if (word[*index] == '}')
			braces--;
		else if (word[*index] == '\\')
			(*index)++;
		(*index)++;
	}
	return (0);
}

int			ft_parse_par_var(char *word, size_t *index, t_txtlist **current)
{
	int		pars;

	(*index)++;
	pars = 1;
	(*current)->token = word[*index] == '(' ? ARTH_EXPR : CMD_SUB;
	while (pars)
	{
		if (word[*index] == '\0')
			return (-1);
		else if (word[*index] == '(')
			pars++;
		else if (word[*index] == ')' && word[(*index) + 1] == ')'
			&& (*current)->token == ARTH_EXPR && pars == 2)
		{
			(*index) += 2;
			return (0);
		}
		else if (word[*index] == ')')
			pars--;
		else if (word[*index] == '\\')
			(*index)++;
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
	(void)dquote;
	if (word[*index] == '`')
	{
		ft_add_txtlist(word, CMD_SUB_BQUOTE, current, *dquote);
		(*current)->start = *index;
		(*index)++;
		while (word[*index] != '`')
		{
			if (word[*index] == '\0')
				return (-1);
			else if (word[*index] == '\\')
				(*index)++;
			(*index)++;
		}
		(*index)++;
		(*current)->len = *index - (*current)->start;
		return (0);
	}
	return (1);
}
