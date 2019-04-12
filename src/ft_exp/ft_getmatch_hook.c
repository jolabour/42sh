/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getmatch_hook.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:57:05 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 13:58:12 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int					ft_getmatch_hookdash(char *word, t_matchlist *match)
{
	int				i;

	if (word[1] == '-' && word[2] && word[2] != ']')
	{
		if (word[0] < word[2])
		{
			i = word[0];
			while (i <= word[2])
			{
				match->hparam[i] = true;
				i++;
			}
		}
		return (3);
	}
	return (0);
}

int					ft_getmatch_hookhook(char *word, t_matchlist *match)
{
	int				class;
	int				i;

	class = 0;
	while (g_classestab[class].name
		&& !ft_strnequ(g_classestab[class].name, word,
		ft_strlen(g_classestab[class].name)))
		class++;
	if (!g_classestab[class].name)
		return (0);
	i = 0;
	while (g_classestab[class].chars[i])
	{
		match->hparam[(int)g_classestab[class].chars[i]] = true;
		i++;
	}
	return (ft_strlen(g_classestab[class].name));
}

int					ft_getmatch_hooknormal(char *word, t_matchlist *match)
{
	match->hparam[(int)*word] = true;
	return (1);
}

int					ft_getmatch_hook_init(t_matchlist *match, char *word)
{
	int				i;

	i = 1;
	if (word[i] == '!')
	{
		match->token = MATCH_RHOOK;
		i++;
	}
	if (word[i] == ']')
	{
		match->hparam[']'] = true;
		i++;
	}
	return (i);
}

t_matchlist			*ft_getmatch_hook(char *word)
{
	t_matchlist		*new;
	int				i;
	int				ret;

	new = NULL;
	if (*word == '[')
	{
		new = ft_new_match(MATCH_HOOK);
		i = ft_getmatch_hook_init(new, word);
		while (word[i] > 0 && word[i] != ']')
		{
			if (!(ret = ft_getmatch_hookdash(word + i, new)))
				if (!(ret = ft_getmatch_hookhook(word + i, new)))
					ret = ft_getmatch_hooknormal(word + i, new);
			i = i + ret;
		}
		if (word[i] < 1)
		{
			new->tparam = '[';
			new->token = MATCH_TEXT;
		}
		new->next = word[i] > 1 ? ft_getmatch_list(word + i + 1)
			: ft_getmatch_list(word + 1);
	}
	return (new);
}
