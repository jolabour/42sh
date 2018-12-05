/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 23:09:07 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/06 00:13:05 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
	static char*operator[] = {"NONE", "PIPE", "SEMI", "GREAT", "LESS","GREAT_AND", "DLESS", "DGREAT"};

	static char*token[] = {"WORD", "OPERATOR", "NEWLINE"};

void		print_lexer(t_42sh *sh)
{
	t_lexer*	temp;

	temp = sh->lexer;
	ft_putendl("_______________ LEXER _______________");
	ft_putstr("--- NB TOKEN = ");
	ft_putnbr(sh->token_nbr);
	ft_putchar('\n');
	while (temp)
	{
		ft_putstr(token[temp->token_type]);
		ft_putstr(" ");
		ft_putstr(operator[temp->operator_type]);
		if (ft_strlen(token[temp->token_type]) + 1 >= 8)
			ft_putstr("    ");
		else
			ft_putstr("        ");
		ft_putstr(temp->str);
		//if (temp->heredoc)
		//	ft_putstr3("\t", "heredoc: ", temp->heredoc);
		ft_putendl("");
		temp = temp->next;
	}
	ft_putendl("_____________________________________");
}
