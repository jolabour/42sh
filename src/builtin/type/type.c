#include "sh.h"

char		*check_is_alias(t_42sh *sh, char *str)
{
	int		i;
	t_alias	*start;
	char	*to_return;

	i = 0;
	start = sh->alias->begin;
	if (sh->alias->size == 0)
		return (NULL);
	while (i < sh->alias->size)
	{
		if (ft_strequ(start->to_sub, str) == 1)
		{
			to_return = ft_strdup(start->sub);
			return (to_return);
		}
		start = start->next;
		i++;
	}
	return (NULL);
}

int			check_is_builtin(t_42sh *sh, char *str)
{
	int		i;

	i = 0;
	while (sh->builtin[i])
	{
		if (ft_strequ(sh->builtin[i], str) == 1)
			return (1);
		i++;
	}
	return (0);
}

void		get_type(t_42sh *sh)
{
	int		i;
	char	*to_print;

	i = 1;
	while (i < sh->argv->size)
	{
		if ((to_print = check_is_alias(sh, sh->argv->argv[i])) != NULL)
		{
			ft_putstr(sh->argv->argv[i]);
			ft_putstr(" is an alias for ");
			ft_putendl(to_print);
			ft_strdel(&to_print);
		}
		else if (check_is_builtin(sh, sh->argv->argv[i]) == 1)
		{
			ft_putstr(sh->argv->argv[i]);
			ft_putendl(" is a shell builtin");
		}
		else if ((to_print = check_access(sh, i)) != NULL)
		{
			ft_putstr(sh->argv->argv[i]);
			ft_putstr(" is ");
			ft_putendl(to_print);
			ft_strdel(&to_print);
		}
		else
		{
			ft_putstr("42sh: type: ");
			ft_putstr(sh->argv->argv[i]);
			ft_putendl(": not found");
		}
		i++;
	}
}

void		builtin_type(t_42sh *sh)
{
	if (sh->argv->size == 1)
		return ;
	else
		get_type(sh);
}
