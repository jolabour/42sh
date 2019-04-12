/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_parse_tilde.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:39:39 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 19:39:49 by geargenc         ###   ########.fr       */
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
