/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmquotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:36:10 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:36:48 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_rmquotes_backslash_condition(char *word, int i, char quote)
{
	return (word[i] == '\\' && quote != '\'' && word[i + 1] && (quote != '\"'
			|| word[i + 1] == '\\' || word[i + 1] == '\"' || word[i + 1] == '$'
			|| word[i + 1] == '`'));
}

void		ft_rmquotes_word(char *word)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (word[i])
	{
		if (ft_rmquotes_backslash_condition(word, i, quote))
		{
			ft_strcpy(word + i, word + i + 1);
			i++;
		}
		else if (word[i] == '\"' && quote != '\'')
		{
			ft_strcpy(word + i, word + i + 1);
			quote = (quote == '\"') ? 0 : '\"';
		}
		else if (word[i] == '\'' && quote != '\"')
		{
			ft_strcpy(word + i, word + i + 1);
			quote = (quote == '\'') ? 0 : '\'';
		}
		else
			i++;
	}
}

void		ft_rmquotes_args(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		ft_rmquotes_word(args[i]);
		i++;
	}
}
