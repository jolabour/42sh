/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 00:46:03 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/25 03:47:32 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	while (*alst)
	{
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		tmp = *alst;
		tmp = NULL;
		*alst = (*alst)->next;
	}
}
