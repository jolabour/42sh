/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 07:22:44 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/12 07:35:30 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_getenv(t_env *list, const char *name, size_t len, t_var_mark *var)
{
	t_var	*tmp;

	if (len < 1)
		return (NULL);
	while (list)
	{
		if (ft_strncmp(list->str, name, len) == 0)
			return (list->str + len);
		list = list->next;
	}
	if (!var)
		return (NULL);
	tmp = var->begin;
	while (tmp)
	{
		if (ft_strnequ(tmp->to_sub, name, len - 1) == 1)
			return (tmp->sub);
		tmp = tmp->next;
	}
	return (NULL);
}
