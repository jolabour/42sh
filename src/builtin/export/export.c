#include "sh.h"

void				check_print(t_42sh *sh, int *i, int *print)
{
	int			j;

	while (sh->argv->argv[*i])
	{
		if (sh->argv->argv[*i][0] == '-')
		{
			j = 0;
			while (sh->argv->argv[*i][j])
			{
				if (sh->argv->argv[*i][j] != 'p')
					return ;
				*print = 1;
				j++;
			}
			*i = *i + 1;
		}
		else
			return ;
	}
}

void			builtin_export(t_42sh *sh)
{
	int			i;
	int			print;
	int			j;
	t_var		*tmp;
	t_env		*new;

	i = 1;
	print = 0;
	check_print(sh, &i, &print);
	while (sh->argv->argv[i])
	{
		if (check_equal(sh->argv->argv[i]) != 1)
		{
			tmp = sh->var->begin;
			j = 0;
			while (j < sh->var->size)
			{
				if (ft_strequ(tmp->to_sub, sh->argv->argv[i]) == 1)
				{
					new = create_node(ft_strcat(ft_strcat(tmp->to_sub, "="), tmp->sub));
					lst_push(&sh->env, new);
					break ;
				}
				j++;
				tmp = tmp->next;
			}
		}
		i++;
	}
}
