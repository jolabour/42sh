/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 01:47:25 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 07:12:26 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_lexer(t_lex *lex, t_42sh *shell)
{
	int		i;
	int		ret;

	while (lex->input[lex->index])
	{
		i = 0;
		while ((ret = g_tokcond[i].cond(lex, shell)) > 0)
			i++;
		if (ret == -1)
		{
			ft_lex_free(lex);
			return (-1);
		}
		if (lex->input[lex->index] == '\0')
			ft_lex_delimiter(lex, shell);
	}
	return (0);
}
