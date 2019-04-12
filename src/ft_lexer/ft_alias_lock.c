/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias_lock.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:46:02 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 21:40:29 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

bool				ft_check_alias_lock(t_alias_lock **list, size_t min,
					char *alias)
{
	t_alias_lock	**begin;
	t_alias_lock	*tmp;

	begin = list;
	while (*list)
	{
		if ((*list)->ignore < min)
		{
			tmp = (*list)->next;
			free((*list)->alias);
			free(*list);
			*list = tmp;
		}
		else
			list = &((*list)->next);
	}
	tmp = *begin;
	while (tmp)
	{
		if (ft_strequ(tmp->alias, alias))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void				ft_add_len_alias_lock(t_alias_lock *list, int size)
{
	while (list)
	{
		list->ignore = list->ignore + size;
		list = list->next;
	}
}

void				ft_add_alias_lock(t_alias_lock **list, char *name,
					size_t size)
{
	t_alias_lock	*new;

	new = (t_alias_lock *)ft_malloc_exit(sizeof(t_alias_lock));
	new->alias = name;
	new->ignore = size;
	new->next = *list;
	*list = new;
}

bool				ft_match_alias_lock(t_alias_lock *list, size_t index)
{
	while (list)
	{
		if (list->ignore - 1 == index)
			return (true);
		list = list->next;
	}
	return (false);
}

void				ft_free_alias_lock(t_alias_lock **list)
{
	t_alias_lock	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->alias);
		free(*list);
		*list = tmp;
	}
}
