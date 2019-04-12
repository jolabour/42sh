/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gather_splits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:39:40 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:39:55 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_count_args(char ***splits)
{
	int		size;
	int		i;
	int		j;

	size = 0;
	j = 0;
	while (splits[j])
	{
		i = 0;
		while (splits[j][i])
		{
			i++;
			size++;
		}
		j++;
	}
	return (size);
}

char		**ft_gather_splits(char ***splits)
{
	char	**args;
	int		size;
	int		i;
	int		j;

	args = (char **)ft_malloc_exit((ft_count_args(splits) + 1)
		* sizeof(char *));
	size = 0;
	j = 0;
	while (splits[j])
	{
		i = 0;
		while (splits[j][i])
		{
			args[size] = splits[j][i];
			i++;
			size++;
		}
		free(splits[j]);
		j++;
	}
	args[size] = NULL;
	free(splits);
	return (args);
}
