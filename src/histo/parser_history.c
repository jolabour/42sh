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

void substitute_history(t_42sh *sh, int *i)
{
	char *substitute;
	int nb_del;

	substitute = NULL;
	nb_del = 0;
	if (sh->stdin->input[*i + 1] == '!')
	{
		substitute = ft_strdup(sh->history_mark->begin->next->str);
		nb_del = 2;
	}
	else if (sh->stdin->input[*i + 1] == '-')
		substitute = search_history_last(sh, get_nb_history(sh, *i, &nb_del));
	else if (sh->stdin->input[*i + 1] >= '0' && sh->stdin->input[*i + 1] <= '9')
	{
		substitute = search_history_begin(sh, get_nb_history(sh, *i, &nb_del));
	}
	else if (sh->stdin->input[*i + 1] == '!')
		substitute  = ft_strdup(sh->history_mark->begin->next->str);
	else if (sh->stdin->input[*i + 1] >= 'a' && sh->stdin->input[*i + 1] <= 'z')
		substitute = search_str_input(sh, *i + 1, &nb_del);
	else
		return;
	if (substitute == NULL)
	{
		ft_putendl("aled");
		sh->history_mark->error_code = 1;
		// add error_return
		return ;
	}
	get_substitute(sh, *i, substitute, nb_del);
	*i += ft_strlen(substitute) - 1;
	free(substitute);
}

void check_substitute_history(t_42sh *sh)
{
	int i;

	if (sh->history_mark->size == 1)
		return ;
	i = 0;
	while (sh->stdin->input[i])
	{
		if (sh->stdin->input[i] == '!')
			substitute_history(sh, &i);
		i++;
	}
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
		    check_substitute_history(sh);
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
