/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ctrlr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:50:26 by ttresori          #+#    #+#             */
/*   Updated: 2019/02/18 22:50:28 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	get_new_line_ctrlr(t_42sh *sh, char *dup)
{
	ft_strcpy(sh->stdin->input, dup);
	sh->stdin->cursor_pos = sh->prompt_len + sh->stdin->line_pos;
	ft_puts_red(sh->stdin->input);
}

void	clean_line_lentoback(int len_to_left)
{
	while (len_to_left >= 0)
	{
		tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
		len_to_left--;
	}
	tputs(tgetstr("dl", NULL), 0, putchar_custom);
}

int		check_following(char *to_find, char *search,
int start_search, int len_check)
{
	int i;

	i = 0;
	while (len_check > 0)
	{
		if (to_find[i] != search[start_search])
			return (-1);
		len_check--;
		start_search++;
		i++;
	}
	return (1);
}

int		is_in_str(char *to_find, char *search, int len_check)
{
	int i;
	int real_return;

	i = 0;
	real_return = -1;
	while (search[i])
	{
		if (search[i] == to_find[0])
		{
			if (check_following(to_find, search, i, len_check) == 1)
				real_return = 0;
		}
		i++;
	}
	return (real_return);
}
