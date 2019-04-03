/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 04:05:37 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/03 04:15:11 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		del_history(t_history_mark *history)
{
	t_history	*tmp;

	while (history->size > 0)
	{
		tmp = history->begin;
		history->begin = history->begin->next;
		if (history->begin == NULL)
			history->last = NULL;
		else
			history->begin->prev = NULL;
		ft_strdel(&tmp->str);
		free(tmp);
		history->size--;
	}
	free(history);
}

t_history	*new_history(char *line)
{
	t_history	*new;

	new = (t_history*)ft_malloc_exit(sizeof(t_history));
	new->str = ft_strdup(line);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		add_to_list(t_42sh *sh, char *line)
{
	t_history	*new;

	new = new_history(line);
	if (sh->history_mark->size == 0)
	{
		new->next = sh->history_mark->last;
		new->prev = sh->history_mark->begin;
		sh->history_mark->begin = new;
		sh->history_mark->last = new;
	}
	else
	{
		new->prev = NULL;
		new->next = sh->history_mark->begin;
		sh->history_mark->begin->prev = new;
		sh->history_mark->begin = new;
	}
	sh->history_mark->size++;
}
