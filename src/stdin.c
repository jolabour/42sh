/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 09:09:06 by jolabour          #+#    #+#             */
/*   Updated: 2018/09/06 01:29:27 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
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

/*static int			check_input_aled(unsigned char *input, t_42sh *sh)
{
	if (UP_KEY(input))
		return (1);
	else if (DOWN_KEY(input))
		return (1);
	else if (TAB(input))
		return (1);
	else if (OPT_B(input))
	{
		move_to_begin_word(sh);
		return (1);
	}
	else if (OPT_F(input))
	{
		move_to_end_word(sh);
		return (1);
	}
	else if (RIGHT_KEY(input))
	{
		move_to_right(sh);
		return (1);
	}
	else if (PAGE_UP(input))
	{
		move_up(sh);
		return (1);
	}
	else if (PAGE_DOWN(input))
	{
		move_down(sh);
		return (1);
	}
	else if (LEFT_KEY(input))
	{
		move_to_left(sh);
		return (1);
	}
	else if (HOME(input))
	{
		move_to_start(sh);
		return (1);
	}
	else if (END(input))
	{
		move_to_end(sh);
		return (1);
	}
	else if (CTRL_D(input))
	{
		insert_mode_off();
		exit(0);
	}
	else if (CTRL_C(input))
	{
		ft_putchar('\n');
		return (-1);
	}
	else if (DEL(input))
	{
		delete_input_buf(sh);
		return (1);
	}
	else if (OPT_C(input) || OPT_X(input))
	{
		//ft_putchar('a');
		select_mode(sh);
		return (1);
	}
	else if (OPT_V(input))
	{
		if (sh->str_to_paste != NULL)
			ft_paste(sh);
		return (1);
	}
	else if (input[0] < 32 || input[0] > 255)
		return (1);
	return (0);
}
*/
int					get_line(t_42sh *sh)
{
	int				i;
	long			buf;

	sh->str_to_paste = NULL;
	sh->line_pos = 0;
	sh->len_line = 0;
	insert_mode_on();
	sh->input[0] = '\0';
	while (42)
	{
		buf = 0;
		if ((i = read(0, &buf, 3)) > 0)
		{
			if (buf == '\n')
			{
				ft_putchar('\n');
				insert_mode_off();
				ft_strdel(&sh->str_to_paste);
				return (1);
			}
					//printf("length record:%d\n", i);
			if ((i = check_input(sh, buf)) != 1)
			{
				if (i == -1)
					return (0);
				ft_putchar_fd(buf, 0);
				add_char(buf, sh);
			}
		}
	}
}
