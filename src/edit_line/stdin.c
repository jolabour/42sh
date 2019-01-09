/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 09:09:06 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/17 05:50:28 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "sh.h"

int		get_winsize(void)
{
	struct winsize ws;

	ioctl(0, TIOCGWINSZ, &ws);
	return (ws.ws_col);
}

void		ft_paste(t_42sh *sh)
{
	int		len;
	int		i;
	char	tmp[256];

	if (sh->stdin->str_to_paste == NULL)
		return ;
	i = 0;
	len = ft_strlen(sh->stdin->str_to_paste);
	if (sh->stdin->len_line + len >= sh->stdin->size_of_input - 10)
		up_input(sh);
	ft_strcpy(tmp, sh->stdin->input + sh->stdin->line_pos);
	ft_strcpy(sh->stdin->input + sh->stdin->line_pos, sh->stdin->str_to_paste);
	ft_strcpy(sh->stdin->input + sh->stdin->line_pos + len, tmp);
	sh->stdin->len_line += len;
}

void			ft_putlstr_fd(char *str, int fd, int len)
{
	int			i;

	i = 0;
	while (str[i] && i < len)
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
}

int				get_curent_line(t_42sh *sh)
{
	int			pos;

	sh->winsize = get_winsize();
	pos = (sh->stdin->cursor_pos) / (sh->winsize);
	return (pos);
}

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
	tputs(tgoto(tgetstr("ch", NULL), sh->prompt_len, sh->prompt_len), 0, putchar_custom);
	tputs(tgetstr("cd", NULL), 0, putchar_custom);
	ft_putstr_fd(sh->stdin->input, 0);
	tputs(tgoto(tgetstr("rc", NULL), 0, 0), 0, putchar_custom);
}

static void		init_stdin(t_42sh *sh)
{
	if (!(sh->stdin = malloc(sizeof(t_stdin))))
		print_error(_ENOMEM, 1);
	sh->stdin->size_of_input = 1000;
	if (!(sh->stdin->input = malloc(sizeof(char) * sh->stdin->size_of_input)))
		print_error(_ENOMEM, 1);
	sh->stdin->input[0] = '\0';
	sh->stdin->line_pos = 0;
	sh->stdin->len_line = 0;
	sh->stdin->str_to_paste = NULL;
	sh->stdin->cursor_pos = sh->prompt_len;
	sh->stdin->nb_line = 0;
	sh->stdin->ctrlc = 0;
	init_history(sh, sh->path_history);
	add_to_list(sh, sh->stdin->input);
	sh->history_mark->cur = sh->history_mark->begin;
	sh->history_mark->pos = 1;
}

int			get_line(t_42sh *sh)
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
				sh->stdin->input[sh->stdin->len_line] = '\n';
				sh->stdin->len_line++;
				while (sh->stdin->line_pos < sh->stdin->len_line)
					move_to_right(sh);
				ft_putchar_fd('\n', 0);
				sh->stdin->input[sh->stdin->len_line] = '\0';
				ft_strdel(&sh->stdin->str_to_paste);
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
