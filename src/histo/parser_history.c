/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:15:18 by ttresori          #+#    #+#             */
/*   Updated: 2019/01/10 19:38:17 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void parser_builtin(t_42sh *sh)
{
	sh->lexer = sh->lexer->next;
    if (ft_strcmp(sh->lexer->str, "-c") == 0)
		clean_history(sh->path_history);
	if (ft_strcmp(sh->lexer->str, "-p") == 0)
		history_p(sh);
	if (ft_strcmp(sh->lexer->str, "-r") == 0)
		print_history_r(sh->path_history);
	if (ft_strcmp(sh->lexer->str, "-n") == 0)
		print_history_n(sh->path_history);
	if (sh->token_nbr == 2)
		print_history(sh->history_mark);
}

static int	is_builtin(t_42sh *sh)
{
	int i;

	i = 1;
	while (i++ != sh->token_nbr)
	{
		if (ft_strcmp(sh->lexer->str, "history") == 0)
			return (0);
		if (sh->lexer->str[0] == '!')
		  {
		    substitute_history(sh);
		    return (-1);
		}
		sh->lexer = sh->lexer->next;
	}
	return (-1);
}

void		parser(t_42sh *sh)
{
	if (is_builtin(sh) == 0)
		parser_builtin(sh);
}
