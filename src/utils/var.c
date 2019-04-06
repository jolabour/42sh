/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 03:29:36 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/06 05:18:05 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char			*get_var(t_42sh *sh, char *str)
{
	char		*substitute;
	int			i;
	t_var		*tmp;

	i = 0;
	tmp = sh->var->begin;
	while (i < sh->var->size)
	{
		if (ft_strequ(tmp->to_sub, str) == 1)
		{
			substitute = ft_strdup(tmp->sub);
			return (substitute);
		}
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

t_var			*new_var(char **line)
{
	t_var *new;

	new = ft_malloc_exit(sizeof(t_var));
	new->to_sub = ft_strdup(line[0]);
	new->sub = ft_strdup(line[1]);
	new->next = NULL;
	return (new);
}

void			add_to_varlist(t_42sh *sh, char **split)
{
	t_var *new;

	if (check_valid_var(split[0]) == 0)
	{
		ft_putendl_fd("variable can contain only alphanumeric caracters.", 2);
		return ;
	}
	if (check_var(&sh->var, split) == 0)
		return ;
	new = new_var(split);
	if (sh->var->size == 0)
		sh->var->begin = new;
	else
	{
		new->next = sh->var->begin;
		sh->var->begin = new;
	}
	sh->var->size++;
}

int				check_env(t_env **env, char **split)
{
	/*
	**			Recherche faite sans le '=' dans l'env...
	*/
	t_env		*tmp;
	int			len;
	char		*new;

	len = ft_strlen(split[0]);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(split[0], tmp->str, len))
		{
			free(tmp->str);
			new = ft_strjoin(split[0], "=");
			tmp->str = ft_strjoin(new, split[1]);
			free(new);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void			check_local_variable(t_42sh *sh, char *str)
{
	char	**split;

	split = ft_strsplitsetone(str, '=');
	if (ft_strequ(split[0], "PATH") == 1)
		reset_hashtable(&sh->hashtable);
	if (check_env(&sh->env, split) != 1)
		add_to_varlist(sh, split);
	free(split[0]);
	free(split[1]);
	free(split);
}
