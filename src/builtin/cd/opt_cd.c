/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 07:34:56 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/11 10:22:01 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			check_str_opt(char *str, t_42sh *sh)
{
	int		i;
	int		opt;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'L')
			opt = 2;
		else if (str[i] == 'P')
			opt = 1;
		else
		{
			ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", 2);
			sh->retval = 1;
			return ((opt = 0));
		}
		i++;
	}
	return (opt);
}

int			check_opt_cd(t_42sh *sh, int *i)
{
	int		opt;

	opt = 2;
	if (sh->argv->size < 2)
		return (2);
	while (sh->argv->argv[*i])
	{
		if (sh->argv->argv[*i][0] != '-' ||
				ft_strequ(sh->argv->argv[*i], "-") == 1)
			return (opt);
		opt = check_str_opt(sh->argv->argv[*i], sh);
		if (opt == 0)
			return (0);
		*i = *i + 1;
	}
	return (opt);
}
