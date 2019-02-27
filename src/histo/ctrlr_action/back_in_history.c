/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_in_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:49:40 by ttresori          #+#    #+#             */
/*   Updated: 2019/02/18 22:49:43 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		print_all_value(t_42sh *sh, char *dup)
{
	ft_putchar('\n');
	ft_puts_blue("sh->stdin->line_pos : ");
	ft_putnbr(sh->stdin->line_pos);
	ft_putchar('\n');
	ft_puts_blue("sh->stdin->len_line : ");
	ft_putnbr(sh->stdin->len_line);
	ft_putchar('\n');
	ft_puts_blue("sh->stdin->cursor_pos : ");
	ft_putnbr(sh->stdin->cursor_pos);
	ft_putchar('\n');
	ft_puts_blue("sh->promt_len; : ");
	ft_putnbr(sh->prompt_len);
	ft_putchar('\n');
	ft_puts_blue("sh->pos_arg ");
	ft_putnbr(sh->history_mark->pos_arg);
	ft_putchar('\n');
	ft_puts_blue("character on cursos ");
	if (dup)
		ft_putchar(dup[sh->stdin->line_pos]);
	ft_putchar('\n');
}

static	int	check_occ_in_dup(t_42sh *sh, char *arg, char *dup)
{
	int i;
	int pos_start;

	pos_start = sh->stdin->line_pos - 1;
	if (pos_start <= 1)
		return (0);
	i = 0;
	while (pos_start >= 0)
	{
		if (arg && dup && arg[0] == dup[pos_start])
			if (check_after(arg, dup, pos_start,
			sh->history_mark->pos_arg) == 1)
			{
				sh->history_mark->line_pos = pos_start;
				sh->history_mark->cursor_pos = sh->prompt_len + pos_start;
				sh->history_mark->nb_moove = i
				+ (sh->stdin->len_line - sh->stdin->line_pos) + 1;
				return (1);
			}
		pos_start--;
		i++;
	}
	return (1);
}

void		back_in_history(t_42sh *sh, char *dup, char *arg)
{
	if (check_occ_in_dup(sh, arg, dup) == 1)
		return ;
	else
	{
		sh->history_mark->dup_select++;
		sh->history_mark->line_pos = -1;
		sh->history_mark->cursor_pos = -1;
		sh->history_mark->nb_moove = -1;
	}
}
