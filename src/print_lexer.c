/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 23:09:07 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/06 01:07:08 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
	static char*operator[] = {"         ", "PIPE     ", "SEMI     ", "GREAT    ", "LESS     ","GREATAND ", "DLESS    ", "DGREAT   "};

	static char*token[] = {"WORD     ", "OPERATOR ", "NEWLINE  "};

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
		ft_putstr(temp->str);
		ft_putendl("");
		temp = temp->next;
	}
	ft_putendl("_____________________________________");
}
