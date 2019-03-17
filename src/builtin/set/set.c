#include "sh.h"

void	list_var(t_42sh *sh)
{
	t_var	*tmp;
	int		i;

	i = 0;
	tmp = sh->var->begin;
	if (sh->var->size == 0)
		return ;
	while (i < sh->var->size)
	{
		ft_putstr(tmp->to_sub);
		ft_putstr("=");
		ft_putstr(tmp->sub);
		ft_putstr("\n");
		tmp = tmp->next;
		i++;
	}
}

void		builtin_set(t_42sh *sh)
{
	list_var(sh);
	sh->retval = 0;
}
