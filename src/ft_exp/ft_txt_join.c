/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_txt_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:33:14 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:55:32 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

size_t			ft_txt_len(t_txtlist *list)
{
	size_t		count;

	count = 0;
	while (list)
	{
		list->len = ft_strlen(list->data);
		count = count + list->len;
		list = list->next;
	}
	return (count);
}

char			*ft_txt_join(t_txtlist *list)
{
	t_txtlist	*tmp;
	char		*word;
	size_t		size;

	word = (char *)ft_malloc_exit((ft_txt_len(list) + 1) * sizeof(char));
	word[0] = '\0';
	size = 0;
	while (list)
	{
		ft_strcpy(word + size, list->data);
		size = size + list->len;
		tmp = list;
		list = list->next;
		free(tmp->data);
		free(tmp);
	}
	return (word);
}
