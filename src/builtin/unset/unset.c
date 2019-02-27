#include "sh.h"

void		lst_del_var(t_var **var, t_var *to_del, t_var *prev)
{
	if (*var == to_del)
		*var = to_del->next;
	else
		prev->next = to_del->next;
	free(to_del->sub);
	free(to_del->to_sub);
	free(to_del);
}

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

void		del_var(t_42sh *sh)
{
	int		i;
	int		j;

	i = 1;
	while (sh->argv->argv[i])
	{
		if ((j = search_var(sh->var, &sh->var->begin, sh->argv->argv[i])) == 0)
		{
			ft_putstr("42sh: unset: ");
			ft_putstr(sh->argv->argv[i]);
			ft_putstr(": not found\n");
		}
		if (j == 1)
			sh->var->size--;
		i++;
	}
}

void		builtin_unset(t_42sh *sh)
{
	if (sh->argv->size == 1)
		ft_putstr("unset: usage: unset [name ...]\n");
	else
		del_var(sh);
}
