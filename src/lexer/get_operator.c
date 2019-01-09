/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 20:54:35 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/05 23:43:55 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				check_operator_great(char c)
{
	if (!ft_is_blank(c) && !ft_is_newline(c) && c == '>')
		return (1);
	return (0);
}

int				check_operator_and(char c)
{
	if (!ft_is_blank(c) && !ft_is_newline(c) && c == '&')
		return (1);
	return (0);
}

int				check_operator_less(char c)
{
	if (!ft_is_blank(c) && !ft_is_newline(c) && c == '<')
		return (1);
	return (0);
}

static int		get_type(t_42sh *sh)
{
	int			operator_type;

	operator_type = 0;
	if (sh->stdin->input[sh->lex_pos] == '<')
	{
		if (check_operator_less(sh->stdin->input[sh->lex_pos + 1]))
			operator_type = DLESS;
		else
			operator_type = LESS;
	}
	else if (sh->stdin->input[sh->lex_pos] == '>')
	{
		if (check_operator_great(sh->stdin->input[sh->lex_pos + 1]))
			operator_type = DGREAT;
		else if (check_operator_and(sh->stdin->input[sh->lex_pos + 1]))
			operator_type = GREATAND;
		else
			operator_type = GREAT;
	}
	else if (sh->stdin->input[sh->lex_pos] == ';')
		operator_type = SEMI;
	else if (sh->stdin->input[sh->lex_pos] == '|')
		operator_type = PIPE;
	return (operator_type);
}

void			get_operator(t_42sh *sh)
{
	int			i;
	int			len;
	char		*str;

	len = 1;
	i = get_type(sh);
	if (i > LESS)
	{
		if (!(str = ft_strsub(sh->stdin->input, sh->lex_pos, 2)))
			print_error(_ENOMEM, 1);
		len++;
	}
	else
	{
		if (!(str = ft_strsub(sh->stdin->input, sh->lex_pos, 1)))
			print_error(_ENOMEM, 1);
	}
	add_token(sh, str, OPERATOR, i, 0);
	ft_strdel(&str);
	sh->lex_pos += len;
	sh->token_nbr++;
}
