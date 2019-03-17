#include "sh.h"

void				check_print(t_42sh *sh, int *i, int *print)
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
				if (sh->argv->argv[*i][j] != 'p')
				{
					*print = 0;
					return ;
				}
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

void			print_export(t_42sh *sh)
{
	int			i;

	i = 0;
	while (sh->copy_env[i])
	{
		ft_putstr("export ");
		ft_putendl(sh->copy_env[i]);
		i++;
	}
}

void			builtin_export(t_42sh *sh)
{
	int			i;
	int			print;
	int			j;
	t_var		*tmp;
	t_env		*new;
	char		**split;
	char		*tmp2;
	char		*tmp3;

	i = 1;
	check_print(sh, &i, &print);
	if (print == 1)
	{
		print_export(sh);
		return ;
	}
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
					tmp2 = ft_strjoin(sh->argv->argv[i], "=");
					tmp3 = ft_strjoin(tmp2, tmp->sub);
					new = create_node(tmp3);
					lst_push(&sh->env, new);
					free(tmp2);
					free(tmp3);
					if (search_var(sh->var, &sh->var->begin, sh->argv->argv[i]) == 1)
						sh->var->size--;
					break ;
				}
				j++;
				tmp = tmp->next;
			}
		}
		else
		{
			split = ft_strsplitsetone(sh->argv->argv[i], '=');
			if (check_env(&sh->env, split) == 1)
			{
				if (ft_strequ(split[0], "PATH") == 1)
					reset_hashtable(&sh->hashtable);
			}
			else
			{
				new = create_node(sh->argv->argv[i]);
				lst_push(&sh->env, new);
			}
			if (search_var(sh->var, &sh->var->begin, split[0]) == 1)
				sh->var->size--;
			free(split[0]);
			free(split[1]);
			free(split);
		}
		i++;
	}
	sh->retval = 0;
}
