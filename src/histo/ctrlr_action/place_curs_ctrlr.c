/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_curs_ctrlr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:50:12 by ttresori          #+#    #+#             */
/*   Updated: 2019/02/18 22:50:14 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			check_after(char *arg, char *dup, int i2, int len_arg)
{
	int check;

	check = 0;
	while (check < len_arg)
	{
		if (arg[check] == '\0' || dup[i2] == '\0')
			return (-1);
		if (arg[check] != dup[i2])
			return (-1);
		check++;
		i2++;
	}
	return (1);
}

static int	get_last_c_of_occurence(char *arg, char *dup, int len_arg)
{
	int i;
	int i2;
	int real_return;

	i = 0;
	i2 = 0;
	real_return = -1;
	while (dup[i2])
	{
		if (arg[i] == dup[i2])
			if (check_after(arg, dup, i2, len_arg) == 1)
				real_return = i2;
		i2++;
	}
	return (real_return);
}

static void	move_curs_on_str(t_42sh *sh, int nb_to_move, char *dup)
{
	int len_dup;

	len_dup = ft_strlen(dup);
	nb_to_move = len_dup - nb_to_move;
	sh->stdin->len_line = len_dup;
	sh->history_mark->line_pos > -1
		? (sh->stdin->line_pos = sh->history_mark->line_pos)
		: (sh->stdin->line_pos = len_dup - nb_to_move);
	sh->history_mark->cursor_pos > -1
		? (sh->stdin->cursor_pos = sh->history_mark->cursor_pos)
		: (sh->stdin->cursor_pos = sh->prompt_len
		+ sh->stdin->len_line - nb_to_move);
	if (sh->history_mark->nb_moove > -1)
		nb_to_move = sh->history_mark->nb_moove;
	while (nb_to_move-- > 0)
		tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
}

void		place_curs_ctrlr(t_42sh *sh, char *arg, char *dup)
{
	int i;
	int nb_to_move;

	i = 0;
	nb_to_move = 0;
	if (!arg || !dup)
	{
		sh->stdin->len_line = 0;
		sh->stdin->cursor_pos = sh->prompt_len;
		sh->stdin->line_pos = 0;
		return ;
	}
	if ((nb_to_move = get_last_c_of_occurence(arg, dup,
	sh->history_mark->pos_arg)) > -1)
		move_curs_on_str(sh, nb_to_move, dup);
}
