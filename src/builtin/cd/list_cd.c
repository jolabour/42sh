/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 07:30:22 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/11 08:40:22 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_path			*create_node_path(char *str)
{
	t_path		*new;

	new = (t_path*)ft_malloc_exit(sizeof(*new));
	new->str = ft_strdup(str);
	new->next = NULL;
	return (new);
}

void			lst_push_path(t_path **head, t_path *new)
{
	t_path		*tmp;

	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_path			*set_list_path(char **split, t_42sh *sh)
{
	t_path		*start;
	t_path		*new;
	int			i;

	start = NULL;
	i = 0;
	while (split[i])
	{
		new = create_node_path(split[i]);
		lst_push_path(&start, new);
		i++;
	}
	sh->path->size = i;
	return (start);
}

void			get_list(char *str, t_42sh *sh)
{
	char		**split;

	split = ft_strsplit_with(str, '/');
	sh->path->begin = set_list_path(split, sh);
	ft_free_split(split);
}

void			lst_del_path(t_path **path, t_path *to_del, t_path *prev)
{
	if (*path == to_del)
		*path = to_del->next;
	else
		prev->next = to_del->next;
	free(to_del->str);
	free(to_del);
}
