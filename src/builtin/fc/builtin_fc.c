/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:37:09 by ttresori          #+#    #+#             */
/*   Updated: 2019/02/18 23:38:00 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"

void	print_nb_and_str(t_42sh *sh, int nb, char *str)
{
	if (sh->history_mark->print_nb_line == 0)
	{
		ft_putnbr(nb);
		ft_putstr("\t");
	}
	ft_putl_cyan(str);
}

void	print_delimit_history(t_42sh *sh, int start, int stop)
{
	t_history	*tmp;
	int			i;

	i = 0;
	if (sh->history_mark->reverse_print == 1)
	{
		tmp = sh->history_mark->begin->next->next;
		while (i < sh->history_mark->size && tmp)
		{
			if (i >= start && i <= stop)
				print_nb_and_str(sh, i, tmp->str);
			tmp = tmp->next;
			i++;
		}
		return ;
	}
	tmp = sh->history_mark->last;
	while (i < sh->history_mark->size - 2)
	{
		if (i >= start && i <= stop)
			print_nb_and_str(sh, i, tmp->str);
		tmp = tmp->prev;
		i++;
	}
}

void	check_for_l_opt(t_42sh *sh)
{
	if (sh->history_mark->size < 2)
	{
		ft_putendl("42sh: fc: history specification out of range");
		return ;
	}
	if (sh->argv->size == 1 || ft_strcmp(sh->argv->argv[1], "-n") == 0)
	{
		edit_last_command(sh);
		return ;
	}
	else if (ft_strcmp(sh->argv->argv[1], "-l") >= 0)
	{
		if (ft_strchr(sh->argv->argv[1], 'r'))
			sh->history_mark->reverse_print = 1;
		if (ft_strchr(sh->argv->argv[1], 'n')) // MODIFY THIS SHIT
			sh->history_mark->print_nb_line = 1;
		if (sh->argv->argv[2] == NULL)     // -l NULL
		{
			print_delimit_history(sh, sh->history_mark->size - 16,
					sh->history_mark->size);
			return ;
		}
		// if (sh->argv->argv[2] && sh->argv->argv[3] == NULL)    // -l 1 NULL
		//  print_delimit_history(sh, ft_atoi(sh->argv->argv[2]), sh->history_mark->size);
		if (check_if_alpha(sh) == 1)
			return ;
		if (check_if_digit(sh) == 1)
			return ;
	}
}

void	builtin_fc(t_42sh *sh)
{
	sh->history_mark->print_nb_line = 0;
	sh->history_mark->reverse_print = 0;
	check_for_l_opt(sh);
}
