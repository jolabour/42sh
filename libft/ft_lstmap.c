/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 03:38:46 by jolabour          #+#    #+#             */
/*   Updated: 2017/11/20 06:35:41 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_lst;
	t_list *bgn;

	if (!(new_lst = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	bgn = new_lst;
	*new_lst = (*f(lst));
	lst = lst->next;
	while (lst != NULL)
	{
		new_lst->next = (t_list *)malloc(sizeof(t_list));
		new_lst = new_lst->next;
		*new_lst = (*f(lst));
		lst = lst->next;
	}
	return (bgn);
}
