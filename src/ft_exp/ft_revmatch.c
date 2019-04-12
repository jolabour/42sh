/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revmatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:02:14 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:02:21 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_matchlist		*ft_revmatch_rev(t_matchlist *l1)
{
	t_matchlist *ret;
	t_matchlist	*l2;

	l2 = l1->next;
	if (l2)
	{
		ret = ft_revmatch_rev(l2);
		l1->next = NULL;
		l2->next = l1;
		return (ret);
	}
	return (l1);
}

t_matchlist		*ft_revmatch(t_matchlist *list)
{
	t_matchlist	*ret;
	t_matchlist	*tmp;

	ret = ft_revmatch_rev(list);
	tmp = ret;
	ret = ret->next;
	tmp->next = NULL;
	list->next = tmp;
	return (ret);
}
