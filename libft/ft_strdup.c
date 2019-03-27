/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 02:31:52 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/27 00:10:33 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *src)
{
	int		i;
	char	*str;

	i = 0;
	while (src[i])
		i++;
	if (!(str = (char*)ft_malloc_exit(sizeof(char) * (i + 1))))
		return (0);
	str = ft_strcpy(str, src);
	return (str);
}
