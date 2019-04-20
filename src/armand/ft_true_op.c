/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_true_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:20:31 by achavy            #+#    #+#             */
/*   Updated: 2019/04/20 00:28:43 by achavy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** 1='<' 2='>' 3='<=' 4='>=' 5='==' 6='!='
*/

static int		ft_check_op(char *str)
{
	if (str[1] == '\0')
		return (0);
	if (str[0] == '<' && str[1] != '=')
		return (1);
	if (str[0] == '>' && str[1] != '=')
		return (2);
	if (str[0] == '<' && str[1] == '=')
		return (3);
	if (str[0] == '>' && str[1] == '=')
		return (4);
	if (str[0] == '=' && str[1] == '=')
		return (5);
	if (str[0] == '!' && str[1] == '=')
		return (6);
	return (0);
}

static void		ft_check_last_true(char *str, int p, int nb, int *i)
{
	if (nb == 4)
	{
		if (ft_atoi(&str[p]) >= ft_atoi(&str[i[0] + 2]))
			ft_itoa_exp_ari(&str[p], 1, i[1] + 1);
		else
			ft_itoa_exp_ari(&str[p], 0, i[1] + 1);
	}
	else if (nb == 5)
	{
		if (ft_atoi(&str[p]) == ft_atoi(&str[i[0] + 2]))
			ft_itoa_exp_ari(&str[p], 1, i[1] + 1);
		else
			ft_itoa_exp_ari(&str[p], 0, i[1] + 1);
	}
	else if (nb == 6)
	{
		if (ft_atoi(&str[p]) != ft_atoi(&str[i[0] + 2]))
			ft_itoa_exp_ari(&str[p], 1, i[1] + 1);
		else
			ft_itoa_exp_ari(&str[p], 0, i[1] + 1);
	}
}

static void		ft_check_true(char *str, int p, int nb, int *i)
{
	if (nb == 1)
	{
		if (ft_atoi(&str[p]) < ft_atoi(&str[i[0] + 1]))
			ft_itoa_exp_ari(&str[p], 1, i[1]);
		else
			ft_itoa_exp_ari(&str[p], 0, i[1]);
	}
	else if (nb == 2)
	{
		if (ft_atoi(&str[p]) > ft_atoi(&str[i[0] + 1]))
			ft_itoa_exp_ari(&str[p], 1, i[1]);
		else
			ft_itoa_exp_ari(&str[p], 0, i[1]);
	}
	else if (nb == 3)
	{
		if (ft_atoi(&str[p]) <= ft_atoi(&str[i[0] + 2]))
			ft_itoa_exp_ari(&str[p], 1, i[1] + 1);
		else
			ft_itoa_exp_ari(&str[p], 0, i[1] + 1);
	}
	else
		ft_check_last_true(str, p, nb, i);
	i[0] = -1;
}

char			*ft_true_op(char *str, int size)
{
	int i[2];
	int nb;
	int p;

	i[0] = 0;
	nb = 0;
	p = -1;
	i[1] = -1;
	while (i[0] < size)
	{
		if (0 != (nb = ft_check_op(&str[i[0]])))
		{
			if (nb < 3)
				i[1] = i[0] + ft_count_next_num(&str[i[0] + 1]) + 1;
			else
				i[1] = i[0] + ft_count_next_num(&str[i[0] + 2]) + 1;
			p = ft_count_prev_num(str, i[0]) - i[0];
			ft_check_true(str, p, nb, i);
			str = ft_erase_space(str);
			size = ft_strlen(str);
			nb = 0;
		}
		i[0] = i[0] + 1;
	}
	return (ft_logic_op(str, size));
}
