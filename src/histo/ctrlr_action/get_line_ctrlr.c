/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_ctrlr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:50:05 by ttresori          #+#    #+#             */
/*   Updated: 2019/02/18 22:50:07 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	*check_exit(t_42sh *sh, char *arg, long buf)
{
	if (buf == '\n' || buf == CTRL_D || buf == UP_KEY || buf == DOWN_KEY
			|| buf == LEFT_KEY || buf == RIGHT_KEY)
	{
		sh->history_mark->error_code = 0;
		sh->history_mark->ctrlr_arg = ft_strdup(arg);
		free(arg);
		return (NULL);
	}
	if (buf == CTRL_C)
	{
		sh->history_mark->error_code = 1;
		sh->history_mark->ctrlr_arg = ft_strdup(arg);
		free(arg);
		return (NULL);
	}
	return (arg);
}

static char	*realloc_when_find(t_42sh *sh, char *arg, long buf)
{
	arg = ft_realloc(arg, sh->history_mark->pos_arg,
	sh->history_mark->pos_arg + 2);
	arg[sh->history_mark->pos_arg] = buf;
	arg[sh->history_mark->pos_arg + 1] = '\0';
	sh->history_mark->pos_arg++;
	return (arg);
}

static char	*add_char_arg(t_42sh *sh, char *arg, long buf)
{
	if (sh->history_mark->pos_arg == 0)
	{
		arg = ft_realloc(arg, 0, 2);
		if (buf != DEL)
			arg[0] = buf;
		else
		{
			sh->history_mark->is_find = 0;
			arg[0] = '\0';
		}
		arg[1] = '\0';
		sh->history_mark->pos_arg = 1;
	}
	else
	{
		if (sh->history_mark->is_find == 1)
			arg = realloc_when_find(sh, arg, buf);
	}
	sh->history_mark->error_code = 0;
	return (arg);
}

static char	*get_char(t_42sh *sh, char *arg, long buf, char *dup)
{
	if (buf == TAB)
		return (arg);
	if (!(check_exit(sh, arg, buf)))
		return (NULL);
	if (buf == CTRL_R)
	{
		back_in_history(sh, dup, arg);
		return (arg);
	}
	if (buf == DEL)
	{
		if (sh->history_mark->pos_arg == 0)
		{
			arg[0] = '\0';
			return (arg);
		}
		arg = ft_realloc(arg, sh->history_mark->pos_arg,
		sh->history_mark->pos_arg);
		arg[sh->history_mark->pos_arg - 1] = '\0';
		sh->history_mark->pos_arg--;
		return (arg);
	}
	return (add_char_arg(sh, arg, buf));
}

char		*get_line_ctrlr(t_42sh *sh, char *arg, char *dup)
{
	long	buf;
	int		i;

	buf = 0;
	if ((i = read(0, &buf, 6)) > 0)
	{
		arg = get_char(sh, arg, buf, dup);
		return (arg);
	}
	return (NULL);
}
