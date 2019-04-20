/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:03:25 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/20 04:04:03 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

bool			ft_match_end(char *str, t_matchlist *match)
{
	(void)match;
	if (!*str)
		return (true);
	return (false);
}

bool			ft_match_text(char *str, t_matchlist *match)
{
	if (*str != match->tparam)
		return (false);
	return (g_matchtab[match->next->token](str + 1, match->next));
}

bool			ft_match_wcard(char *str, t_matchlist *match)
{
	return ((*str && g_matchtab[match->token](str + 1, match))
			|| g_matchtab[match->next->token](str, match->next));
}

bool			ft_match_qmark(char *str, t_matchlist *match)
{
	if (!*str)
		return (false);
	return (g_matchtab[match->next->token](str + 1, match->next));
}
