/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getmatch_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:12:17 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:12:24 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_getmatch_free(t_matchlist *list)
{
	t_matchlist	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}
