/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 00:57:29 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/12 08:23:40 by jolabour         ###   ########.fr       */
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

int			check_name_alias(char *str, t_42sh *sh)
{
	int		i;

	i = 0;
	if (str[0] == '-' || str[0] == '=')
		return ((sh->retval = 1));
	while (str[i])
	{
		if (str[i] == '/')
			return ((sh->retval = 1));
		i++;
	}
	return (0);
}

void		add_alias(t_42sh *sh)
{
	char	**split;
	int		i;

	i = 1;
	while (sh->argv->argv[i])
	{
		split = ft_strsplitsetone(sh->argv->argv[i], '=');
		if (sh->argv->argv[i][0] != '=' &&
				check_name_alias(sh->argv->argv[i], sh) == 0)
		{
			if (split[1] == NULL)
			{
				if (print_alias(sh, split[0]) != 0)
					print_error_alias(split[0], sh, 1);
			}
			else
				add_to_list_alias(sh, split);
		}
		else
			print_error_alias(split[0], sh, 2);
		i++;
		ft_free_split(split);
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
