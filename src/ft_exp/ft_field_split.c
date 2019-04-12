/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_field_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:41:33 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:42:40 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

size_t		ft_count_field_size(char *word, char *sep)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (word[i] && (quote || !ft_strchr(sep, word[i])))
	{
		if (word[i] == '\\' && quote != '\'' && word[i + 1])
			i++;
		else if (word[i] == '\"' && quote != '\'')
			quote = quote ? 0 : '\"';
		else if (word[i] == '\'' && quote != '\"')
			quote = quote ? 0 : '\'';
		i++;
	}
	return (i);
}

int			ft_count_fields(char *word, char *sep)
{
	size_t	i;
	int		fields;

	i = 0;
	fields = 0;
	while (word[i])
	{
		while (word[i] && ft_strchr(sep, word[i]))
			i++;
		if (word[i])
		{
			fields++;
			i = i + ft_count_field_size(word + i, sep);
		}
	}
	return (fields);
}

char		**ft_field_split_word(char *word, char *sep)
{
	char	**split;
	int		i;
	int		fields;
	size_t	field_size;

	split = (char **)ft_malloc_exit((ft_count_fields(word, sep) + 1)
		* sizeof(char *));
	i = 0;
	fields = 0;
	while (word[i])
	{
		while (word[i] && ft_strchr(sep, word[i]))
			i++;
		if (word[i])
		{
			field_size = ft_count_field_size(word + i, sep);
			split[fields] = ft_strsub(word, i, field_size);
			i = i + field_size;
			fields++;
		}
	}
	split[fields] = NULL;
	return (split);
}

char		**ft_field_split(char **args, t_42sh *shell)
{
	char	***splits;
	char	*sep;
	int		i;

	i = 0;
	while (args[i])
		i++;
	splits = (char ***)ft_malloc_exit((i + 1) * sizeof(char **));
	sep = ft_getvar("IFS", shell);
	if (!sep)
		sep = ft_strdup(" \t\n");
	i = 0;
	while (args[i])
	{
		splits[i] = ft_field_split_word(args[i], sep);
		free(args[i]);
		i++;
	}
	splits[i] = NULL;
	free(args);
	free(sep);
	return (ft_gather_splits(splits));
}
