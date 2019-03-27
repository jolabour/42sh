/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 01:04:33 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/27 01:06:13 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			check_opt(t_42sh *sh)
{
	if (sh->argv->argv[1][0] != '-')
		return (1);
	if (ft_strequ(sh->argv->argv[1], "-a") != 1)
	{
		ft_putstr_fd("42sh: unalias: ", 2);
		ft_putstr_fd(sh->argv->argv[1], 2);
		ft_putendl_fd(": invalid option", 2);
		ft_putstr_fd("unalias: usage: unalias [-a] name [name ...]\n", 2);
		sh->retval = 1;
		return (-1);
	}
	return (2);
}

int			search_alias(t_alias_mark *alias_mark, t_alias **alias, char *str)
{
	t_alias	*tmp;
	t_alias	*prev;
	int		i;

	i = 0;
	tmp = *alias;
	prev = tmp;
	while (i < alias_mark->size)
	{
		if (ft_strequ(tmp->to_sub, str) == 1)
		{
			lst_del(alias, tmp, prev);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
		i++;
	}
	return (0);
}

void		del_all(t_alias_mark *alias)
{
	t_alias	*tmp;

	while (alias->size > 0)
	{
		tmp = alias->begin;
		alias->begin = alias->begin->next;
		ft_strdel(&tmp->to_sub);
		ft_strdel(&tmp->sub);
		free(tmp);
		alias->size--;
	}
}

void		del_alias(t_42sh *sh)
{
	int		i;
	int		j;

	if ((i = check_opt(sh)) == -1)
		return ;
	if (i == 2)
	{
		del_all(sh->alias);
		return ;
	}
	while (sh->argv->argv[i])
	{
		if ((j = search_alias(sh->alias,
				&sh->alias->begin, sh->argv->argv[i])) == 0)
		{
			ft_putstr_fd("42sh: unalias: ", 2);
			ft_putstr_fd(sh->argv->argv[i], 2);
			ft_putstr_fd(": not found\n", 2);
			sh->retval = 1;
		}
		if (j == 1)
			sh->alias->size--;
		i++;
	}
}

void		builtin_unalias(t_42sh *sh)
{
	if (sh->argv->size == 1)
	{
		ft_putstr_fd("unalias: usage: unalias [-a] name [name ...]\n", 2);
		sh->retval = 1;
	}
	else
		del_alias(sh);
	if (sh->retval == 1)
		return ;
	sh->retval = 0;
}
