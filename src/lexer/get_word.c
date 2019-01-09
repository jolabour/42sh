/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 20:33:55 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/06 19:44:04 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				check_word(char c)
{
	if (!ft_is_blank(c) && ft_isprint(c) && !ft_is_newline(c) && !ft_is_operator(c))
		return (1);
	return (0);
}

int				get_dquote(t_42sh *sh, int i, int *quote)
{
	*quote = 3;
	i++;
	while (sh->stdin->input[sh->lex_pos + i] != '\0' && sh->stdin->input[sh->lex_pos + i] != '"' && sh->stdin->input[sh->lex_pos + i] != '\n')
	{
		if (sh->stdin->input[sh->lex_pos + i] == '\\')
			i++;
		i++;
	}
	if (sh->stdin->input[sh->lex_pos + i] == '"')
		*quote = 0;
	i++;
	return (i);
}

int				get_squote(t_42sh *sh, int i, int *quote)
{
	*quote = 2;
	i++;
	while (sh->stdin->input[sh->lex_pos + i] != '\0' && sh->stdin->input[sh->lex_pos + i] != '\'' && sh->stdin->input[sh->lex_pos + i] != '\n')
		i++;
	if (sh->stdin->input[sh->lex_pos + i] == '\'')
		*quote = 0;
	i++;
	return (i);
}

void			get_word(t_42sh *sh)
{
	char		*str;
	int			i;
	int			quote;

	quote = 0;
	i = 0;
	while (sh->stdin->input[sh->lex_pos + i] != '\0' && check_word(sh->stdin->input[sh->lex_pos + i]))
	{
		if (sh->stdin->input[sh->lex_pos + i] == '\\')
		{
			quote = 1;
			i++;
		}
		if (!quote && sh->stdin->input[sh->lex_pos + i] == '\'')
			i = i + get_squote(sh, i, &quote);
		else if (!quote && sh->stdin->input[sh->lex_pos + i] == '"')
			i = i + get_dquote(sh, i, &quote);
		else
		{
			if (sh->stdin->input[sh->lex_pos + i] != '\n')
				quote = 0;
			i++;
		}
	}
	if (!(str = ft_strsub(sh->stdin->input, sh->lex_pos, i)))
		print_error(_ENOMEM, 1);
	add_token(sh, str, WORD, NONE, quote);
	sh->lex_pos = sh->lex_pos + i;
	ft_strdel(&str);
	sh->token_nbr++;
}
