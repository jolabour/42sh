/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 03:54:56 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/20 02:03:44 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				check_print(t_42sh *sh, int *i, int *print)
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
					return (0);
				*print = 1;
				j++;
			}
			*i = *i + 1;
		}
		else
		{
			*print = 0;
			return (1);
		}
	}
	return (1);
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
	j = -1;
	if (check_tmp_env(sh, str) == 1)
		return ;
	while (++j < sh->var->size)
	{
		if (ft_strequ(tmp->to_sub, str) == 1)
		{
			tmp2 = ft_strjoin(str, "=");
			tmp3 = ft_strjoinfree(tmp2, tmp->sub, 1);
			new = create_node(tmp3);
			lst_push(&sh->env, new);
			free(tmp3);
			if (search_var(sh->var, &sh->var->begin, str) == 1)
				sh->var->size--;
			break ;
		}
		tmp = tmp->next;
	}
}

void			check_export(t_42sh *sh, int *i)
{
	char		**split;

	while (sh->argv->argv[*i])
	{
		split = ft_strsplitsetone(sh->argv->argv[*i], '=');
		if (check_name(split[0]) == 0)
		{
			ft_putendl_fd("invalid variable name.", 2);
			if (sh->retval != 2)
				sh->retval = 1;
		}
		else if (check_equal(sh->argv->argv[*i]) != 1)
		{
			export_equal(sh, sh->argv->argv[*i]);
			sh->retval = 2;
		}
		else
		{
			export_not_equal(sh, sh->argv->argv[*i]);
			sh->retval = 2;
		}
		ft_free_split(split);
		*i = *i + 1;
	}
}

void			builtin_export(t_42sh *sh)
{
	int			i;
	int			print;

	i = 1;
	sh->retval = 0;
	if (check_print(sh, &i, &print) == 0)
	{
		print_error_export(sh, i);
		return ;
	}
	if (print == 1)
	{
		print_export(sh);
		return ;
	}
	check_export(sh, &i);
	if (sh->retval == 2)
		sh->retval = 0;
}
