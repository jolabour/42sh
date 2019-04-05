/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 09:09:06 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/05 05:59:03 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "sh.h"

void			clean_print(t_42sh *sh)
{
	int			i;
	int			pos_line;

	i = 0;
	pos_line = get_curent_line(sh);
	sh->stdin->nb_line = (sh->prompt_len + sh->stdin->len_line) / (sh->winsize);
	tputs(tgoto(tgetstr("sc", NULL), 0, 0), 0, putchar_custom);
	while (i < pos_line)
	{
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 0, putchar_custom);
		i++;
	}
	tputs(tgoto(tgetstr("ch", NULL), sh->prompt_len,
		sh->prompt_len), 0, putchar_custom);
	tputs(tgetstr("cd", NULL), 0, putchar_custom);
	ft_putstr_fd(sh->stdin->input, 0);
	tputs(tgoto(tgetstr("rc", NULL), 0, 0), 0, putchar_custom);
}

static void		get_pos_cursor_begin(t_42sh *sh)
{
	char		*tmp;
	int			fl;
	char		buf[1024];

	if (isatty(STDIN_FILENO))
	{
		fl = fcntl(STDIN_FILENO, F_GETFL);
		fcntl(STDIN_FILENO, F_SETFL, fl | O_NONBLOCK);
		while (read(STDIN_FILENO, buf, 1024) > 0)
			continue ;
		fcntl(STDIN_FILENO, F_SETFL, fl);
		ft_putstr("\033[6n");
		buf[read(STDOUT_FILENO, buf, 1023)] = '\0';
		tmp = ft_strchr(buf, ';');
		tmp++;
		sh->prompt_len = ft_atoi(tmp) - 1;
	}
	sh->stdin->cursor_pos = sh->prompt_len;
}

static void		init_stdin(t_42sh *sh)
{
	sh->stdin = (t_stdin*)ft_malloc_exit(sizeof(t_stdin));
	sh->stdin->size_of_input = 1000;
	sh->stdin->input = (char*)ft_malloc_exit(
		sizeof(char) * sh->stdin->size_of_input);
	sh->stdin->input[0] = '\0';
	sh->stdin->line_pos = 0;
	sh->stdin->len_line = 0;
	sh->stdin->str_to_paste = NULL;
	sh->stdin->nb_line = 0;
	sh->stdin->ctrlc = 0;
	init_history(sh, sh->path_history);
	add_to_list(sh, sh->stdin->input);
	sh->history_mark->cur = sh->history_mark->begin;
	sh->history_mark->pos = 1;
	if (tcsetattr(0, TCSANOW, &sh->term) == -1)
	{
		ft_putendl("tcsetattr: Error.");
		exit(0);
	}
	get_pos_cursor_begin(sh);
}

void			finish_read(t_42sh *sh)
{
	sh->stdin->input[sh->stdin->len_line] = '\n';
	sh->stdin->len_line++;
	while (sh->stdin->line_pos < sh->stdin->len_line)
		move_to_right(sh);
	ft_putchar_fd('\n', 0);
	sh->stdin->input[sh->stdin->len_line] = '\0';
	ft_strdel(&sh->stdin->str_to_paste);
	reset_term(sh);
}

int				get_line(t_42sh *sh)
{
	long	buf;
	int		i;

	init_stdin(sh);
	while (42)
	{
		buf = 0;
		if ((i = read(0, &buf, 6)) > 0)
		{
			if (buf == '\n')
			{
				finish_read(sh);
				return (1);
			}
			if ((i = check_input(sh, buf)) != 1)
			{
				if (i == -1 || (sh->stdin->ctrlc == 1 && i == 2))
					return (0);
				if (i == 2)
					clean_print(sh);
			}
		}
	}
}
