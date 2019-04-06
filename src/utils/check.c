/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 03:27:39 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/06 04:08:05 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			check_equal(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int			check_var(t_var_mark **var, char **split)
{
	int		i;
	t_var	*start;

	i = 0;
	start = (*var)->begin;
	if ((*var)->size == 0)
		return (-1);
	while (i < (*var)->size)
	{
		if (ft_strequ(start->to_sub, split[0]) == 1)
		{
			ft_strdel(&start->sub);
			start->sub = ft_strdup(split[1]);
			return (0);
		}
		start = start->next;
		i++;
	}
	return (-1);
}

int			check_valid_var(char *str)
{
	int		i;

	i = 0;
	if (ft_isalpha(str[i]) != 1)
		return (0);
	while (str[i])
	{
		if (ft_isalnum(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}
