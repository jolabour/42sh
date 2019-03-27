/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 00:57:29 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/27 03:42:37 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			print_alias(t_42sh *sh, char *str)
{
	t_alias	*tmp;
	int		i;

	i = 0;
	tmp = sh->alias->begin;
	if (sh->alias->size == 0)
		return (-1);
	while (i < sh->alias->size)
	{
		if (ft_strequ(tmp->to_sub, str) == 1)
		{
			ft_putstr(tmp->to_sub);
			ft_putstr("='");
			ft_putstr(tmp->sub);
			ft_putstr("'\n");
			return (0);
		}
		tmp = tmp->next;
		i++;
	}
	return (-1);
}

int			check_alias(t_alias_mark **alias, char **split)
{
	int		i;
	t_alias	*start;

	i = 0;
	start = (*alias)->begin;
	if ((*alias)->size == 0)
		return (-1);
	while (i < (*alias)->size)
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

void		add_alias(t_42sh *sh)
{
	char	**split;
	int		i;

	i = 1;
	while (sh->argv->argv[i])
	{
		split = ft_strsplitset(sh->argv->argv[i], "=\n");
		if (split[1] == NULL)
		{
			if (print_alias(sh, split[0]) != 0)
			{
				ft_putstr_fd("42sh: alias: ", 2);
				ft_putstr_fd(split[0], 2);
				ft_putendl_fd(": not found", 2);
				sh->retval = 1;
			}
		}
		else
			add_to_list_alias(sh, split);
		ft_free_split(split);
		i++;
	}
}

void		builtin_alias(t_42sh *sh)
{
	if (sh->argv->size == 1)
		list_alias(sh);
	else
		add_alias(sh);
	if (sh->retval == 1)
		return ;
	sh->retval = 0;
}
