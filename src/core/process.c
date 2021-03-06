/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 07:47:49 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/25 05:06:29 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char			*check_access(t_42sh *sh, int pos)
{
	int				i;
	char			*tmp;
	char			*tmp2;

	i = -1;
	tmp2 = NULL;
	if (access(sh->argv->argv[pos], F_OK) == 0 && sh->argv->argv[pos][0] == '/')
		return (ft_strdup(sh->argv->argv[pos]));
	else if (sh->bin_dirs)
		while (sh->bin_dirs[++i])
		{
			tmp = ft_strjoin(sh->bin_dirs[i], "/");
			tmp2 = ft_strjoin(tmp, sh->argv->argv[pos]);
			ft_strdel(&tmp);
			if (access(tmp2, F_OK) == 0)
				return (tmp2);
			ft_strdel(&tmp2);
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
			res = ft_strdup(tmp->sub);
			return (res);
		}
		tmp = tmp->next;
		i++;
	}
	return (NULL);
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
	t_lex		lex;
	t_ast		ast;

	sh->prompt = NULL;
	g_intr = 0;
	sh->stopexe = 0;
	prompt(sh->env, sh);
	if (get_line(sh) == -1)
		return ;
	if (sh->stdin->len_line == 0)
		ft_exit(sh);
	add_history(sh, sh->stdin->input, sh->path_history);
	lex = (t_lex){ft_strdup(sh->stdin->input), 0, NULL, NULL, true, false, 0};
	if (!ft_lexer(&lex, sh) && lex.begin)
	{
		ast = (t_ast){NULL, NULL, ft_toklist_to_node(&lex)};
		ft_build_ast(&ast, sh);
		if (ast.begin && sh->exit_lock)
			sh->exit_lock--;
		if (ast.begin)
			g_exetab[ast.begin->token](ast.begin, sh);
		ft_ast_free(ast.begin);
	}
	ft_check_jobs(sh);
}
