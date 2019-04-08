/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 05:57:55 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/09 00:17:03 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			search_var(t_var_mark *var_mark, t_var **var, char *str)
{
	t_var	*tmp;
	t_var	*prev;
	int		i;

	i = 0;
	tmp = *var;
	prev = tmp;
	while (i < var_mark->size)
	{
		if (ft_strequ(tmp->to_sub, str) == 1)
		{
			lst_del_var(var, tmp, prev);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
		i++;
	}
	return (0);
}

int			search_env(t_env **env, char *str, size_t len)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = tmp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, str, len))
		{
			list_del(env, tmp, prev);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

void		del_var(t_42sh *sh)
{
	int		i;
	int		j;

	i = 1;
	while (sh->argv->argv[i])
	{
		if (ft_strequ(sh->argv->argv[i], "PATH") == 1)
			reset_hashtable(&sh->hashtable);
		if ((j = search_var(sh->var, &sh->var->begin, sh->argv->argv[i])) == 0)
			search_env(&sh->env, sh->argv->argv[i],
				ft_strlen(sh->argv->argv[i]));
		if (j == 1)
			sh->var->size--;
		i++;
	}
}

void		builtin_unset(t_42sh *sh)
{
	if (sh->argv->size == 1)
	{
		ft_putstr_fd("unset: usage: unset [name ...]\n", 2);
		sh->retval = 1;
		return ;
	}
	del_var(sh);
	sh->retval = 0;
}
