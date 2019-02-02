#include "sh.h"

void	list_alias(t_42sh *sh)
{
	t_alias	*tmp;
	int		i;

	i = 0;
	tmp = sh->alias->begin;
	if (sh->alias->size == 0)
		return ;
	while (i < sh->alias->size)
	{
		ft_putstr(tmp->to_sub);
		ft_putstr("='");
		ft_putstr(tmp->sub);
		ft_putstr("'\n");
		tmp = tmp->next;
		i++;
	}
}

int		print_alias(t_42sh *sh, char *str)
{
	t_alias	*tmp;
	int		i;

	i = 0;
	tmp = sh->alias->begin;
	if (sh->alias->size == 0)
		return (-1);
	while (i < sh->alias->size)
	{
		if (ft_strequ(tmp->to_sub, str) == 1)
		{
			ft_putstr(tmp->to_sub);
			ft_putstr("='");
			ft_putstr(tmp->sub);
			ft_putstr("'\n");
			return (0);
		}
		tmp = tmp->next;
		i++;
	}
	return (-1);
}

t_alias	*new_alias(char **line)
{
	t_alias *new;

	if (!(new = malloc(sizeof(t_alias))))
		print_error(_ENOMEM, 1);
	new->to_sub = ft_strdup(line[0]);
	new->sub = ft_strdup(line[1]);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_to_list_alias(t_42sh *sh, char **split)
{
	t_alias *new;

	new = new_alias(split);
	if (sh->alias->size == 0)
	{
		new->next = sh->alias->last;
		new->prev = sh->alias->begin;
		sh->alias->begin = new;
		sh->alias->last = new;
	}
	else
	{
		new->prev = NULL;
		new->next = sh->alias->begin;
		sh->alias->begin->prev = new;
		sh->alias->begin = new;
	}
	sh->alias->size++;
}

void		add_alias(t_42sh *sh)
{
	char	**split;
	int		i;

	i = 1;
	while (sh->argv->argv[i])
	{
		split = ft_strsplitset(sh->argv->argv[i], "=\n");
		if (split[1] == NULL)
		{
			if (print_alias(sh, split[0]) != 0)
			{
				ft_putstr("42sh: alias: ");
				ft_putstr(split[0]);
				ft_putendl(": not found");
			}
		}
		else
			add_to_list_alias(sh, split);
		ft_free_split(split);
		i++;
	}
}

void		builtin_alias(t_42sh *sh)
{
	if (sh->argv->size == 1)
		list_alias(sh);
	else
		add_alias(sh);
}
