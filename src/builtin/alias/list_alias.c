/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 00:57:50 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/10 08:28:23 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	list_alias(t_42sh *sh)
{
	t_alias	*tmp;
	int		i;

	i = 0;
	tmp = sh->alias->begin;
	if (sh->alias->size == 0)
		return ;
	while (i < sh->alias->size)
	{
		ft_putstr(tmp->to_sub);
		ft_putstr("='");
		ft_putstr(tmp->sub);
		ft_putstr("'\n");
		tmp = tmp->next;
		i++;
	}
}

t_alias	*new_alias(char **line)
{
	t_alias *new;

	new = (t_alias*)ft_malloc_exit(sizeof(t_alias));
	new->to_sub = ft_strdup(line[0]);
	new->sub = ft_strdup(line[1]);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	lst_del(t_alias **alias, t_alias *to_del, t_alias *prev)
{
	if (*alias == to_del)
		*alias = to_del->next;
	else
		prev->next = to_del->next;
	free(to_del->sub);
	free(to_del->to_sub);
	free(to_del);
}

void	add_to_list_alias(t_42sh *sh, char **split)
{
	t_alias *new;

	if (check_alias(&sh->alias, split) == 0)
		return ;
	new = new_alias(split);
	if (sh->alias->size == 0)
	{
		new->next = sh->alias->last;
		new->prev = sh->alias->begin;
		sh->alias->begin = new;
		sh->alias->last = new;
	}
	else
	{
		new->prev = NULL;
		new->next = sh->alias->begin;
		sh->alias->begin->prev = new;
		sh->alias->begin = new;
	}
	sh->alias->size++;
}
