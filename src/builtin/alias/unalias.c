#include "sh.h"

void		lst_del(t_alias **alias, t_alias *to_del, t_alias *prev)
{
	if (*alias == to_del)
		*alias = to_del->next;
	else
		prev->next = to_del->next;
	free(to_del->sub);
	free(to_del->to_sub);
	free(to_del);
}

int			check_opt(t_42sh *sh)
{
	if (sh->argv->argv[1][0] != '-')
		return (1);
	if (ft_strequ(sh->argv->argv[1], "-a") != 1)
	{
		ft_putstr("42sh: unalias: ");
		ft_putstr(sh->argv->argv[1]);
		ft_putendl(": invalid option");
		ft_putstr("unalias: usage: unalias [-a] name [name ...]\n");
		return (-1);
	}
	return (2);
}

int			search_alias(t_alias_mark *alias_mark, t_alias **alias, char *str)
{
	t_alias	*tmp;
	t_alias	*prev;
	int		i;

	i = 0;
	tmp = *alias;
	prev = tmp;
	while (i < alias_mark->size)
	{
		if (ft_strequ(tmp->to_sub, str) == 1)
		{
			lst_del(alias, tmp, prev);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
		i++;
	}
	return (0);
}

void		del_all(t_alias_mark *alias)
{
	t_alias	*tmp;

	while (alias->size > 0)
	{
		tmp = alias->begin;
		alias->begin = alias->begin->next;
		ft_strdel(&tmp->to_sub);
		ft_strdel(&tmp->sub);
		free(tmp);
		alias->size--;
	}
}

void		del_alias(t_42sh *sh)
{
	int		i;
	int		j;

	if ((i = check_opt(sh)) == -1)
		return ;
	if (i == 2)
	{
		del_all(sh->alias);
		return ;
	}
	while (sh->argv->argv[i])
	{
		if ((j = search_alias(sh->alias, &sh->alias->begin, sh->argv->argv[i])) == 0)
		{
			ft_putstr("42sh: unalias: ");
			ft_putstr(sh->argv->argv[i]);
			ft_putstr(": not found\n");
		}
		if (j == 1)
			sh->alias->size--;
		i++;
	}
}

void		builtin_unalias(t_42sh *sh)
{
	if (sh->argv->size == 1)
		ft_putstr("unalias: usage: unalias [-a] name [name ...]\n");
	else
		del_alias(sh);
}
