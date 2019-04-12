/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getmatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:59:37 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:54:58 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_matchlist			*ft_new_match(t_matchtok token)
{
	t_matchlist		*new;

	new = (t_matchlist *)ft_malloc_exit(sizeof(t_matchlist));
	ft_bzero(new, sizeof(t_matchlist));
	new->token = token;
	return (new);
}

t_matchlist			*ft_getmatch_wcard(char *word)
{
	t_matchlist		*new;

	new = NULL;
	if (*word == '*')
	{
		new = ft_new_match(MATCH_WCARD);
		new->next = ft_getmatch_list(word + 1);
	}
	return (new);
}

t_matchlist			*ft_getmatch_qmark(char *word)
{
	t_matchlist		*new;

	new = NULL;
	if (*word == '?')
	{
		new = ft_new_match(MATCH_QMARK);
		new->next = ft_getmatch_list(word + 1);
	}
	return (new);
}

t_matchlist			*ft_getmatch_text(char *word)
{
	t_matchlist		*new;

	new = ft_new_match(MATCH_TEXT);
	new->tparam = *word;
	new->next = ft_getmatch_list(word + 1);
	return (new);
}

t_matchlist			*ft_getmatch_list(char *word)
{
	t_matchlist		*new;
	int				i;

	if (word[0] < 1)
		new = ft_new_match(MATCH_NONE);
	else
	{
		i = 0;
		while (!(new = g_getmatchtab[i](word)))
			i++;
	}
	return (new);
}
