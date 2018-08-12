/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 09:09:06 by jolabour          #+#    #+#             */
/*   Updated: 2018/08/11 03:54:12 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include <stdio.h>

void		ft_paste(t_42sh *sh)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(sh->str_to_paste);
	ft_putstr_fd(sh->str_to_paste, 0);
	while (i < len)
	{
		add_char(sh->str_to_paste[i], sh);
		i++;
	}
}

int			check_input(unsigned char *input, t_42sh *sh)
{
	if (UP_KEY)
		return (1);
	else if (DOWN_KEY)
		return (1);
	else if (TAB)
		return (1);
	else if (OPT_B)
	{
		move_to_begin_word(sh);
		return (1);
	}
	else if (OPT_F)
	{
		move_to_end_word(sh);
		return (1);
	}
	else if (RIGHT_KEY)
	{
		move_to_right(sh);
		return (1);
	}
	/*else if (PAGE_UP)
	{
		move_up(sh);
		return (1);
	}*/
	else if (PAGE_DOWN)
	{
		move_down(sh);
		return (1);
	}
	else if (LEFT_KEY)
	{
		move_to_left(sh);
		return (1);
	}
	/*else if (HOME)
	{
		move_to_start(sh);
		return (1);
	}*/
	else if (END)
	{
		move_to_end(sh);
		return (1);
	}
	else if (CTRL_D)
	{
		insert_mode_off();
		exit(0);
	}
	else if (CTRL_C)
	{
		ft_putchar('\n');
		return (-1);
	}
	else if (DEL)
	{
		delete_input_buf(sh);
		return (1);
	}
	else if (OPT_C)
	{
		//ft_putchar('a');
		select_mode(sh);
		return (1);
	}
	else if (HOME)
	{
		if (sh->str_to_paste != NULL)
			ft_paste(sh);
		return (1);
	}
	else if (input[0] < 32 || input[0] > 255)
		return (1);
	return (0);
}

int					get_line(t_42sh *sh)
{
	int				i;
	unsigned char	buf[7];

	sh->str_to_paste = NULL;
	sh->line_pos = 0;
	sh->len_line = 0;
	while (42)
	{
		if ((i = read(0, buf, 6)) > 0)
		{
			buf[i] = '\0';
			if (buf[0] == '\n')
			{
				ft_putchar('\n');
				sh->input[sh->len_line] = '\0';
				insert_mode_off();
				ft_strdel(&sh->str_to_paste);
				return (1);
			}
			if ((i = check_input(buf, sh)) != 1)
			{
				if (i == -1)
					return (0);
				ft_putstr_fd((char *)buf, 0);
				add_char(buf[0], sh);
			}
		}
	}
}
