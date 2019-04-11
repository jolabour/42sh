/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 03:50:31 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/11 05:47:23 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_exit(t_42sh *sh)
{
	t_joblist	*jobs;

	if (!sh->pgid)
		ft_putendl_fd("exit", 2);
	if (sh->exit_lock)
		exit((unsigned char)sh->retval);
	jobs = sh->jobs;
	while (jobs)
	{
		if (jobs->stopped)
		{
			ft_putendl_fd("There are stopped jobs.", 2);
			sh->exit_lock = 2;
			sh->retval = 1;
			return ;
		}
		jobs = jobs->next;
	}
	exit((unsigned char)sh->retval);
}

bool			ft_isnumeric(char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\r' || *str == '\v' || *str == '\f')
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

void			builtin_exit(t_42sh *sh)
{
	if (sh->argv->size == 2)
	{
		if (!ft_isnumeric(sh->argv->argv[1]))
		{
			ft_putstr_fd("42sh: exit: ", 2);
			ft_putstr_fd(sh->argv->argv[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			sh->retval = 2;
			return ;
		}
		sh->retval = ft_atoi(sh->argv->argv[1]);
	}
	if (sh->argv->size > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		sh->retval = 2;
	}
	else
		ft_exit(sh);
}
