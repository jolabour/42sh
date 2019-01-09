/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 19:38:48 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/13 04:27:30 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int				ft_is_word(char c)
{
	if (!ft_is_blank(c) && ft_isprint(c) && !ft_is_operator(c))
		return (1);
	return (0);
}

int				ft_is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ';' || c == '&')
		return (1);
	return (0);
}

int				ft_is_newline(char c)
{
	if (c == '\n')
		return (1);
	return (0);
}

void			init_lexer(t_42sh *sh)
{
	sh->lex_pos = 0;
	sh->token_nbr = 0;
}

void			ft_lexer(t_42sh *sh)
{
	if (!sh->stdin->input)
		return ;
//	if (!(sh->lexer = malloc(sizeof(t_lexer))))
//		print_error(_ENOMEM, 1);
	init_lexer(sh);
	while (sh->stdin->input[sh->lex_pos] != '\0')
	{
		if (ft_is_blank(sh->stdin->input[sh->lex_pos]))
			sh->lex_pos++;
		else if (ft_is_word(sh->stdin->input[sh->lex_pos]))
			get_word(sh);
		else if (ft_is_operator(sh->stdin->input[sh->lex_pos]))
			get_operator(sh);
		else if (ft_is_newline(sh->stdin->input[sh->lex_pos]))
			get_newline(sh);
	}
}
