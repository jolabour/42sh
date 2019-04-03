/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 04:24:46 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/03 04:26:52 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*search_history_begin(t_42sh *sh, int nb)
{
	int				i;
	t_history		*tmp;
	char			*substitute;
	int				size;

	if (nb == 0)
		return (NULL);
	i = 1;
	tmp = NULL;
	substitute = NULL;
	size = sh->history_mark->size - 1;
	tmp = sh->history_mark->last;
	while (nb != 1)
	{
		if (i >= size)
			return (NULL);
		tmp = tmp->prev;
		nb--;
		i++;
	}
	substitute = ft_strdup(tmp->str);
	return (substitute);
}

char		*search_history_char(t_42sh *sh, char **to_find)
{
	char		*sub;
	int			len_str_to_find;
	int			size_list;
	t_history	*tmp;

	sub = NULL;
	tmp = NULL;
	tmp = sh->history_mark->begin->next;
	size_list = sh->history_mark->size - 1;
	len_str_to_find = ft_strlen(*to_find);
	while (size_list >= 1)
	{
		if (ft_strncmp(*to_find, tmp->str, len_str_to_find) == 0)
			return ((sub = ft_strdup(tmp->str)));
		tmp = tmp->next;
		size_list--;
	}
	return (NULL);
}

char		*search_history_last(t_42sh *sh, int nb)
{
	t_history	*tmp;
	char		*substitute;
	int			size;

	if (nb == 0)
		return (NULL);
	tmp = NULL;
	substitute = NULL;
	size = sh->history_mark->size - 1;
	tmp = sh->history_mark->begin->next;
	if (nb == 0)
		return (NULL);
	while (nb != -1)
	{
		if (size <= 1)
			return (NULL);
		tmp = tmp->next;
		nb++;
		size--;
	}
	substitute = ft_strdup(tmp->str);
	return (substitute);
}
