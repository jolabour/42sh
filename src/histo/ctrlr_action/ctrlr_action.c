/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrlr_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:49:55 by ttresori          #+#    #+#             */
/*   Updated: 2019/02/18 22:49:58 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char		*search_history_ctrl_r(t_42sh *sh, char *to_find)
{
	char		*sub;
	int			size_list;
	int			save_dup_select;
	t_history	*tmp;

	sub = NULL;
	tmp = NULL;
	tmp = sh->history_mark->begin;
	size_list = sh->history_mark->size;
	save_dup_select = sh->history_mark->dup_select;
	while (size_list > 0)
	{
		if ((is_in_str(to_find, tmp->str, sh->history_mark->pos_arg) == 0)
				&& (save_dup_select-- == 0))
			return ((sub = ft_strdup(tmp->str)));
		tmp = tmp->next;
		size_list--;
	}
	sh->history_mark->is_find = 0;
	return (NULL);
}

static void		to_exit_ctrlr(t_42sh *sh, char *dup, char *arg)
{
	sh->history_mark->is_find == 0
	? clean_line_lentoback(sh->history_mark->pos_arg + 25)
	: clean_line_lentoback(sh->history_mark->pos_arg + 16
	+ ft_strlen(dup));
	prompt(sh->env, sh);
	if (dup && sh->history_mark->error_code == 0)
	{
		get_new_line_ctrlr(sh, dup);
		place_curs_ctrlr(sh, sh->history_mark->ctrlr_arg, dup);
		free(sh->history_mark->ctrlr_arg);
	}
	else
		place_curs_ctrlr(sh, NULL, dup);
	free(arg);
	free(dup);
	return ;
}

void			reset_history_curs_pos(t_42sh *sh)
{
	sh->history_mark->cursor_pos = -1;
	sh->history_mark->line_pos = -1;
	sh->history_mark->nb_moove = -1;
	sh->history_mark->dup_select = -1;
	sh->history_mark->is_find = 0;
}

void			ctrlr_read(t_42sh *sh, char *dup, char *arg)
{
	while (42)
	{
		if (!(arg = get_line_ctrlr(sh, arg, dup)))
		{
			to_exit_ctrlr(sh, dup, arg);
			return ;
		}
		if (dup)
			free(dup);
		if ((dup = search_history_ctrl_r(sh, arg)))
		{
			sh->history_mark->is_find = 1;
			print_prompt_search(sh, 0, arg, dup, sh->history_mark->pos_arg);
		}
		else
		{
			print_prompt_search(sh, 1, arg, NULL, sh->history_mark->pos_arg);
			reset_history_curs_pos(sh);
		}
		place_curs_ctrlr(sh, arg, dup);
	}
}

void			ctrlr_action(t_42sh *sh)
{
	char	*arg;
	char	*dup;
	int		is_find;

	dup = NULL;
	is_find = 0;
	arg = NULL;
	sh->history_mark->error_code = 0;
	sh->history_mark->ctrlr_arg = NULL;
	sh->history_mark->pos_arg = 0;
	reset_history_curs_pos(sh);
	sh->history_mark->dup_select = 0;
	if (!(arg = (char*)malloc(sizeof(char) * 0)))
		return ;
	clean_line_lentoback(sh->prompt_len);
	print_prompt_search(sh, 0, NULL, NULL, sh->history_mark->pos_arg);
	sh->stdin->cursor_pos = 16;
	ctrlr_read(sh, dup, arg);
}
