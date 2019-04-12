/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:04:57 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:06:01 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

bool			ft_match_hook(char *str, t_matchlist *match)
{
	if (!match->hparam[(int)*str])
		return (false);
	return (g_matchtab[match->next->token](str + 1, match->next));
}

bool			ft_match_rhook(char *str, t_matchlist *match)
{
	if (!*str || match->hparam[(int)*str])
		return (false);
	return (g_matchtab[match->next->token](str + 1, match->next));
}
