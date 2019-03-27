/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 07:47:49 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/27 06:08:35 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "sh.h"

char			*check_access(t_42sh *sh, int pos)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (access(sh->argv->argv[pos], F_OK) == 0)
	{
		tmp2 = ft_strdup(sh->argv->argv[pos]);
		return (tmp2);
	}
	if (sh->bin_dirs)
	{
		while (sh->bin_dirs[i])
		{
			tmp = ft_strjoin(sh->bin_dirs[i], "/");
			tmp2 = ft_strjoin(tmp, sh->argv->argv[pos]);
			ft_strdel(&tmp);
			if (access(tmp2, F_OK) == 0)
				return (tmp2);
			ft_strdel(&tmp2);
			i++;
		}
	}
	return (NULL);
}

char			*substitute_alias(char *name, t_42sh *sh)
{
	char		*res;
	int			i;
	t_alias		*tmp;

	i = 0;
	tmp = sh->alias->begin;
	while (i < sh->alias->size)
	{
		if (ft_strequ(tmp->to_sub, name) == 1)
		{
			ft_strdel(&name);
			res = ft_strdup(tmp->sub);
			return (res);
		}
		tmp = tmp->next;
		i++;
	}
	return (name);
}

void			free_tab(char **str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		ft_strdel(&str[i]);
		i++;
	}
	free(str);
}

void			process(t_42sh *sh)
{
	void		*list;

	prompt(sh->env, sh);
	if (get_line(sh) != 1)
		return ;
	if (sh->stdin->len_line == 0 || !sh->stdin->input)
		return ;
	check_substitute_history(sh);
	if (sh->history_mark->error_code == 0 &&
		ft_strcmp(sh->stdin->input, "fc\n") != 0)
		add_history(sh, sh->stdin->input, sh->path_history);
	list = ft_lexer(&(sh->stdin->input), sh);
	if (list)
	{
		list = ft_toklist_to_node((sh->stdin->input), list);
		list = ft_build_ast(list, sh);
		if (list)
			g_exetab[((t_node *)list)->token](list, sh);
	}
}
