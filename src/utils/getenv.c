/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 07:22:44 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/10 03:06:18 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_getenv(t_env *list, const char *name, size_t len, t_var_mark *var)
{
	char	*str;
	t_var	*tmp;

	str = NULL;
	if (len < 1)
		return (str);
	while (list)
	{
		if (ft_strncmp(list->str, name, len) == 0)
			return (list->str + len);
		list = list->next;
	}
	if (!var)
		return (NULL);
	tmp = var->begin;
	str = ft_strsub(name, 0, len - 1);
	while (tmp)
	{
		if (ft_strequ(tmp->to_sub, str) == 1)
		{
			free(str);
			return (tmp->sub);
		}
		tmp = tmp->next;
	}
	free(str);
	return (NULL);
}
