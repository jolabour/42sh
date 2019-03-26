/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_exp_ari.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:18:14 by achavy            #+#    #+#             */
/*   Updated: 2019/03/26 11:53:27 by achavy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int		ft_check_digit(char *str, int i)
{
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}

static int		ft_check_op(char *str, int i)
{
	if (str[i])
	{
		if ((str[i] == '+') || (str[i] == '-') || (str[i] == '*')
		|| (str[i] == '/') || (str[i] == '%')
		|| (str[i] == '<' && str[i + 1] != '=')
		|| (str[i] == '>' && str[i + 1] != '='))
			return (i + 1);
		if ((str[i] == '&' && str[i + 1] == '&')
		|| (str[i] == '|' && str[i + 1] == '|')
		|| (str[i] == '<' && str[i + 1] == '=')
		|| (str[i] == '>' && str[i + 1] == '=')
		|| (str[i] == '=' && str[i + 1] == '=') 
		|| (str[i] == '!' && str[i + 1] == '='))
			return (i + 2);
	}
	ft_exp_ari_error(ft_strjoin("operator error or missing : ", str));
	return (-1);
}

static int		ft_check_num(char *str, int i)
{
	if (ft_isdigit(str[i]))
		return (ft_check_digit(str, i + 1));
	if ((str[i] == '-') || (str[i] == '+'))
	{
		i++;
		if (ft_isdigit(str[i]))
			return (ft_check_digit(str, i + 1));
	}
	ft_exp_ari_error(ft_strjoin("operande error or missing : ", str));
	return (-1);
}

int			ft_check_exp_ari(char *str)
{
	int i;
	
	i = 0;
	while (str[i] == ' ' || str[i] == '(' || str[i] == ')')
		i++;
	if ((-1 == (i = ft_check_num(str, i))))
		return (0);	
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '(' || str[i] == ')')
			i++;
		if (!str[i])
			return (1);
		if ((-1 == (i = ft_check_op(str, i))))
			return (0);
		while (str[i] == ' ' || str[i] == '(' || str[i] == ')')
			i++;
		if ((-1 == (i = ft_check_num(str, i))))
			return (0);
	}
	return (1);
}
