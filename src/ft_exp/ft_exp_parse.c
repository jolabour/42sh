/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:42:21 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 12:54:38 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_parse_error(t_txtlist *list)
{
	t_txtlist	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
	ft_putstr_fd("42sh: unexpected '\\0'\n", 2);
}

t_txtlist		*ft_parse_check(t_txtlist *list)
{
	if (list->token)
		return (list);
	free(list);
	return (NULL);
}

t_txtlist		*ft_parse_word(char *word)
{
	t_txtlist	*list[2];
	size_t		index;
	bool		dquote;
	int			i;
	int			ret;

	if (!(list[0] = ft_new_txtlist()))
		return (NULL);
	list[1] = list[0];
	index = 0;
	dquote = false;
	while (word[index])
	{
		i = 0;
		while ((ret = g_txttab[i](word, &index, &(list[1]), &dquote)) == 1)
			i++;
		if (ret < 0)
		{
			ft_parse_error(list[0]);
			return (NULL);
		}
	}
	return (ft_parse_check(list[0]));
}
