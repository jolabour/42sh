/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_parse_text.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:47:33 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/16 01:39:06 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_parse_backslash(char *word, size_t *index,
			t_txtlist **current, bool *dquote)
{
	if (word[*index] == '\\')
	{
		ft_parse_text(word, index, current, dquote);
		if (word[*index])
			(*index)++;
		(*current)->len = *index - (*current)->start;
		return (0);
	}
	return (1);
}

int			ft_parse_quote(char *word, size_t *index,
			t_txtlist **current, bool *dquote)
{
	if (word[*index] == '\'' && !(*dquote))
	{
		ft_parse_text(word, index, current, dquote);
		while (word[*index] && word[*index] != '\'')
			(*index)++;
		if (word[*index])
			(*index)++;
		(*current)->len = *index - (*current)->start;
		return (0);
	}
	return (1);
}

int			ft_parse_text(char *word, size_t *index,
			t_txtlist **current, bool *dquote)
{
	if (word[*index] == '"')
		*dquote = !(*dquote);
	if ((*current)->token != TEXT)
	{
		ft_add_txtlist(word, TEXT, current, *dquote);
		(*current)->start = *index;
	}
	(*current)->len++;
	(*index)++;
	return (0);
}
