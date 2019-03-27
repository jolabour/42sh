/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 03:54:56 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/27 06:20:14 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			check_print(t_42sh *sh, int *i, int *print)
{
	int			j;

	*print = 0;
	while (sh->argv->argv[*i])
	{
		if (sh->argv->argv[*i][0] == '-')
		{
			j = 1;
			while (sh->argv->argv[*i][j])
			{
				if (sh->argv->argv[*i][j] != 'p' && (*print = 0) == 0)
					return ;
				*print = 1;
				j++;
			}
			*i = *i + 1;
		}
		else
		{
			*print = 0;
			return ;
		}
	}
	if (*print == 1)
		return ;
}

void			export_not_equal(t_42sh *sh, char *str)
{
	char		**split;
	t_env		*new;

	split = ft_strsplitsetone(str, '=');
	if (check_env(&sh->env, split) == 1)
	{
		if (ft_strequ(split[0], "PATH") == 1)
			reset_hashtable(&sh->hashtable);
	}
	else
	{
		new = create_node(str);
		lst_push(&sh->env, new);
	}
	if (search_var(sh->var, &sh->var->begin, split[0]) == 1)
		sh->var->size--;
	free(split[0]);
	free(split[1]);
	free(split);
}

void			export_equal(t_42sh *sh, char *str)
{
	int			j;
	t_var		*tmp;
	t_env		*new;
	char		*tmp2;
	char		*tmp3;

	tmp = sh->var->begin;
	j = 0;
	while (j < sh->var->size)
	{
		if (ft_strequ(tmp->to_sub, str) == 1)
		{
			tmp2 = ft_strjoin(str, "=");
			tmp3 = ft_strjoin(tmp2, tmp->sub);
			new = create_node(tmp3);
			lst_push(&sh->env, new);
			free(tmp2);
			free(tmp3);
			if (search_var(sh->var, &sh->var->begin, str) == 1)
				sh->var->size--;
			break ;
		}
		j++;
		tmp = tmp->next;
	}
}

void			check_export(t_42sh *sh, int *i)
{
	while (sh->argv->argv[*i])
	{
		if (check_equal(sh->argv->argv[*i]) != 1)
			export_equal(sh, sh->argv->argv[*i]);
		else
			export_not_equal(sh, sh->argv->argv[*i]);
		*i = *i + 1;
	}
}

void			builtin_export(t_42sh *sh)
{
	int			i;
	int			print;

	i = 1;
	check_print(sh, &i, &print);
	if (print == 1)
	{
		print_export(sh);
		return ;
	}
	check_export(sh, &i);
	sh->retval = 0;
}
