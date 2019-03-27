/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 06:40:41 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/27 00:54:34 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*ft_joinpath(const char *path, const char *name)
{
	char	*join;
	size_t	len_path;

	len_path = ft_strlen(path);
	join = ft_memalloc(len_path + ft_strlen(name) + 2);
	ft_strcpy(join, path);
	join[len_path] = '/';
	ft_strcpy(join + len_path + 1, name);
	return (join);
}
