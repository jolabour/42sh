/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 01:37:38 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/23 10:34:33 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				get_winsize(void)
{
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	return (ws.ws_col);
}

void			ft_move_cursor_left(int start, int end)
{
	int			winsize;

	winsize = get_winsize();
	while (start > end)
	{
		if (start % winsize == 0)
		{
			tputs(tgoto(tgetstr("up", NULL), 1, 0), 1, putchar_custom);
			tputs(tgoto(tgetstr("ch", NULL), winsize - 1, winsize - 1),
					1, putchar_custom);
		}
		else
			tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
		start--;
	}
}

void			ft_paste(t_42sh *sh)
{
	int			len;
	int			i;
	char		*tmp;

	if (sh->stdin->str_to_paste == NULL)
		return ;
	i = 0;
	len = ft_strlen(sh->stdin->str_to_paste);
	if (sh->stdin->len_line + len >= sh->stdin->size_of_input - 10)
		up_input(sh);
	tmp = ft_strdup(sh->stdin->input + sh->stdin->line_pos);
	ft_strcpy(sh->stdin->input + sh->stdin->line_pos, sh->stdin->str_to_paste);
	ft_strcpy(sh->stdin->input + sh->stdin->line_pos + len, tmp);
	free(tmp);
	sh->stdin->len_line += len;
}

int				get_curent_line(t_42sh *sh)
{
	int			pos;

	sh->winsize = get_winsize();
	pos = (sh->stdin->cursor_pos) / (sh->winsize);
	return (pos);
}
