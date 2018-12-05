/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 20:33:55 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/06 00:04:11 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			check_word(char c)
{
	if (!ft_is_blank(c) && ft_isprint(c) && !ft_is_newline(c) && !ft_is_operator(c))
		return (1);
	return (0);
}

void			get_word(t_42sh *sh)
{
	char		*str;
	int			i;

	i = 0;
	while (sh->stdin->input[sh->lex_pos + i] != '\0' && check_word(sh->stdin->input[sh->lex_pos + i]))
		i++;
	if (!(str = ft_strsub(sh->stdin->input, sh->lex_pos, i)))
		print_error(_ENOMEM, 1);
	add_token(sh, str, WORD, NONE);
	sh->lex_pos = sh->lex_pos + i;
	ft_strdel(&str);
	sh->token_nbr++;
}
