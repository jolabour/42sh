/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 07:38:09 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/25 03:35:10 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			lst_del_path_dotdot(t_path **path, t_path *to_del, t_path *prev)
{
	if (*path == to_del)
		*path = to_del->next->next;
	else
		prev->next = to_del->next->next;
	free(to_del->str);
	free(to_del->next->str);
	free(to_del->next);
	free(to_del);
}

void			delete_sdot(t_42sh *sh, t_path **path)
{
	t_path		*prev;
	t_path		*tmp;
	int			i;

	tmp = *path;
	i = 0;
	prev = tmp;
	while (i < sh->path->size)
	{
		if (ft_strequ(tmp->str, "/.") == 1)
		{
			lst_del_path(path, tmp, prev);
			sh->path->size--;
			tmp = *path;
			prev = tmp;
			i = 0;
		}
		else
		{
			i++;
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void			ft_dot_dot(t_42sh *sh, t_path **path)
{
	t_path		*tmp;
	t_path		*prev;
	int			i;

	delete_sdot(sh, path);
	tmp = *path;
	prev = tmp;
	i = -1;
	while (++i + 1 < sh->path->size)
	{
		if (ft_strequ(tmp->next->str, "/..") == 1
				&& ft_strequ(tmp->str, "/..") == 0)
		{
			lst_del_path_dotdot(path, tmp, prev);
			sh->path->size = sh->path->size - 2;
			i = -1;
			tmp = *path;
			prev = tmp;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}
