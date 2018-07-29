/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 01:35:40 by jolabour          #+#    #+#             */
/*   Updated: 2017/11/20 07:11:12 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	if (n < 1)
		return (1);
	while ((s1[i] == s2[i]) && s1[i] && s2[i] && i < n - 1)
		i++;
	if (s1[i] == s2[i])
		return (1);
	return (0);
}
