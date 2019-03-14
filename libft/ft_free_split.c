/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 19:12:21 by ttresori          #+#    #+#             */
/*   Updated: 2019/03/08 00:28:55 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return (NULL);
	while (split[i] != NULL)
		free(split[i++]);
	free(split);
	split = NULL;
	return (split);
}
