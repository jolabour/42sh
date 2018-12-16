/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:15:18 by ttresori          #+#    #+#             */
/*   Updated: 2018/12/12 22:10:29 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void parser_builtin(t_42sh *sh)
{
	sh->lexer = sh->lexer->next;
//	if (sh->token_nbr == 2)
//		print_history(sh->path_history, 0);
    if (ft_strcmp(sh->lexer->str, "-c") == 0)
		clean_history(sh->path_history);
	if (ft_strcmp(sh->lexer->str, "-p") == 0)
		history_p(sh);
	if (ft_strcmp(sh->lexer->str, "-r") == 0)
		print_history_r(sh->path_history);
	if (ft_strcmp(sh->lexer->str, "-n") == 0)
		print_history_n(sh->path_history);
        
}

static int	is_builtin(t_42sh *sh)
{
	int i;

	i = 1;
	while (i++ != sh->token_nbr)
	{
		if (ft_strcmp(sh->lexer->str, "history") == 0)
			return (0);
		sh->lexer = sh->lexer->next;
	}
	return (-1);
}

void		parser(t_42sh *sh)
{
	if (is_builtin(sh) == 0)
		parser_builtin(sh);
}
