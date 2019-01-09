/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 23:09:07 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/06 18:46:58 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
	static char*operator[] = {"  ----   ", "  PIPE   ", "  SEMI   ", "  GREAT  ", "  LESS   ","GREATAND ", " DLESS   ", " DGREAT  "};

	static char*token[] = {"WORD     ", "OPERATOR ", "NEWLINE  "};

void		print_lexer(t_42sh *sh)
{
	t_lexer*	temp;

	temp = sh->lexer;
	ft_putendl("*************** LEXER ***************");
	ft_putstr("---> NB TOKEN = ");
	ft_putnbr(sh->token_nbr);
	ft_putendl("");
	ft_putendl("_____________________________________");
	while (temp)
	{
		ft_putstr(token[temp->token_type]);
		ft_putstr("| ");
		ft_putstr(operator[temp->operator_type]);
		ft_putstr("| ");
		ft_putnbr(temp->quote);
		ft_putstr("| ");
		ft_putendl(temp->str);
		ft_putendl("_____________________________________");
		temp = temp->next;
	}
	ft_putendl("*************************************");
}
