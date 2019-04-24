/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 00:26:26 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/23 10:43:43 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		add_char(long input, t_42sh *sh)
{
	char	*tmp;

	if (sh->stdin->line_pos != sh->stdin->len_line)
	{
		tmp = ft_strdup(&sh->stdin->input[sh->stdin->line_pos]);
		sh->stdin->input[sh->stdin->line_pos] = (char)input;
		ft_strcpy(sh->stdin->input + sh->stdin->line_pos + 1, tmp);
		free(tmp);
		sh->stdin->input[sh->stdin->len_line + 1] = '\0';
	}
	else
	{
		sh->stdin->input[sh->stdin->len_line] = (char)input;
		sh->stdin->input[sh->stdin->len_line + 1] = '\0';
	}
}

void		delete_char(t_42sh *sh)
{
	char	*tmp;

	if (sh->stdin->line_pos != sh->stdin->len_line)
	{
		tmp = ft_strdup(&sh->stdin->input[sh->stdin->line_pos]);
		ft_strcpy(sh->stdin->input + sh->stdin->line_pos - 1, tmp);
		free(tmp);
		sh->stdin->input[sh->stdin->len_line - 1] = '\0';
	}
	else
		sh->stdin->input[sh->stdin->len_line - 1] = '\0';
}

void		delete(void)
{
	tputs(tgetstr("dc", NULL), 1, putchar_custom);
}

void		delete_input_buf(t_42sh *sh)
{
	sh->winsize = get_winsize();
	if (sh->stdin->len_line > 0 && sh->stdin->line_pos > 0)
	{
		delete_char(sh);
		sh->stdin->len_line--;
		free(sh->history_mark->cur->str);
		sh->history_mark->cur->str = ft_strdup(sh->stdin->input);
		move_to_left(sh);
		clean_print(sh);
	}
}

void		delete_input(t_42sh *sh)
{
	if (sh->stdin->line_pos >= 0)
		tputs(tgetstr("dc", NULL), 1, putchar_custom);
}
