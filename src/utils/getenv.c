/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 07:22:44 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/09 00:53:47 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_getenv(t_env *list, const char *name, size_t len)
{
	char	*str;

	str = NULL;
	if (len < 1)
		return (str);
	while (list)
	{
		if (ft_strncmp(list->str, name, len) == 0)
		{
			str = list->str;
			break ;
		}
		list = list->next;
	}
	return (str ? str + len : str);
}
