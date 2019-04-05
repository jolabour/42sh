/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 05:02:51 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/05 05:08:14 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			return_test(t_42sh *sh)
{
	if (sh->argv->size > 3)
	{
		ft_putendl_fd("test: too many arguments", 2);
		sh->retval = 2;
		return (1);
	}
	return (0);
}

int			execute_test(t_42sh *sh, char c, int *pos)
{
	const char			option_tab[OPTION_TEST] = {'b', 'c', 'd', 'e', 'f',
		'g', 'L', 'p', 'r', 'S', 's', 'u', 'w', 'x', 'z'};
	const t_test		action_option[OPTION_TEST] = {test_b, test_c,
		test_d, test_e, test_f, test_g, test_l, test_p, test_r,
		test_su, test_s, test_u, test_w, test_x, test_z};
	int					i;
	struct stat			info;

	i = -1;
	while (++i < OPTION_TEST)
	{
		if (option_tab[i] == c)
		{
			if (lstat(sh->argv->argv[*pos + 2], &info) != 0 &&
				sh->argv->argv[*pos + 1][2] != 'z')
				return (sh->retval = 1);
			if (return_test(sh) > 0)
				return (0);
			action_option[i](sh, info);
			return (1);
		}
	}
	ft_putstr_fd("test: Unknown condition: ", 2);
	ft_putendl_fd(sh->argv->argv[*pos + 1], 2);
	return (sh->retval = 2);
}

int			check_option(t_42sh *sh, int *i)
{
	if (sh->argv->argv[*i + 1][0] == '-' && sh->argv->size > 3)
	{
		ft_putendl_fd("test: too many arguments", 2);
		sh->retval = 2;
		return (1);
	}
	if (sh->argv->argv[*i + 1][0] != '-' && sh->argv->size == 3)
	{
		ft_putstr_fd("42sh: parse error: condition expected: ", 2);
		ft_putendl_fd(sh->argv->argv[*i + 1], 2);
		sh->retval = 2;
		return (1);
	}
	if (sh->argv->argv[*i + 1][0] == '-' && sh->argv->size == 3)
	{
		if (ft_strlen(sh->argv->argv[*i + 1]) != 2)
		{
			ft_putstr_fd("42sh: test: ", 2);
			ft_putstr_fd(sh->argv->argv[*i + 1], 2);
			ft_putendl_fd(": unary operator expected", 2);
			sh->retval = 2;
			return (1);
		}
		execute_test(sh, sh->argv->argv[*i + 1][1], i);
	}
	return (0);
}

int			check_reverse(t_42sh *sh, int *i)
{
	if (sh->argv->size > 2)
	{
		if (ft_strequ(sh->argv->argv[*i + 1], "!") == 1)
		{
			sh->argv->size--;
			*i = *i + 1;
			return (1);
		}
	}
	return (0);
}

void		builtin_test(t_42sh *sh)
{
	int		reverse;
	int		i;

	i = 0;
	if (sh->argv->size == 1)
	{
		sh->retval = 1;
		return ;
	}
	if (sh->argv->size == 2)
	{
		sh->retval = 0;
		return ;
	}
	reverse = check_reverse(sh, &i);
	if (check_option(sh, &i) == 0)
	{
		if (sh->argv->size == 4)
			execute_other_opt(sh, sh->argv->argv[i + 2], &i);
	}
	if (sh->argv->size > 4)
	{
		ft_putendl_fd("test: too many arguments", 2);
		sh->retval = 2;
	}
	if (reverse == 1)
	{
		sh->argv->size++;
		if (sh->retval == 0)
		{
			sh->retval = 1;
			return ;
		}
		sh->retval = 0;
	}
}
