/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:18:14 by achavy            #+#    #+#             */
/*   Updated: 2019/04/11 07:48:17 by achavy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** 1=++* 2=--* 3=*++ 4=*--
*/

static int 		ft_var_modif(char *str, int i, int j, t_list_ari *new)
{
	int		len;

	len = ft_strlen(str);
	if (i > 1)
	{
		if (str[i - 1] == '+' && str[i - 2]	== '+')
		{
			str[i - 1] = ' ';
			str[i - 2] = ' ';
			new->nbr = new->nbr + 1;
			free(new->var);
			new->var = NULL;
			new->var = ft_itoa(new->nbr);
			return (1);
		}
		if (str[i - 1] == '-' && str[i - 2] == '-')
		{
			str[i - 1] = ' ';
			str[i - 2] = ' ';
			new->nbr = new->nbr - 1;
			free(new->var);
			new->var = NULL; 
			new->var = ft_itoa(new->nbr);
			return (2);
		}
	}
	if (j + 1 <= len)
	{
		if (str[j] == '+' && str[j + 1] == '+')
		{
			str[j] = ' ';
			str[j + 1] = ' ';
			return (3);
		}
		if (str[j] == '-' && str[j + 1] == '-')
		{
			str[j] = ' ';
			str[j + 1] = ' ';
			return (4);
		}
	}
	return (0);
}

static char *my_get_var(t_42sh *sh, char *name)
{
	int		i;
	char	*ret;
	t_var	*tmp;

	i = 0;
	tmp = sh->var->begin;
	ret = NULL;
	ft_putendl(name);
	if ((ret = ft_getenv(sh->env, name, ft_strlen(name), NULL)))
		return (ft_strdup(&ret[1]));
	//ft_putstr(name);
	while (i < sh->var->size)
	{
		if (((ft_strcmp(name, tmp->to_sub)) == 0))
			return (ft_strdup(tmp->sub));
		i++;
		tmp = tmp->next;
		ft_putchar('a');
	}
	tmp->next = ft_malloc_exit(sizeof(t_var));
	tmp = tmp->next;
	tmp->next = NULL;
	tmp->to_sub = ft_strdup(name);
	tmp->sub = ft_strdup("0");
	sh->var->size = sh->var->size + 1;
	return (ft_strdup("0"));
}

static char	*ft_replace_var(char *str, t_list_ari **list_var, size_t *i, t_42sh *sh)
{
	t_list_ari	*l_tmp;	
	char		*tmp;
	char 		*new;
	char		*nb;
	int			j;
	char 		*name;

	j = 1;
	nb = NULL;
	new = NULL;
	tmp = NULL;
	name = NULL;
	l_tmp = NULL;
	ft_putstr("bgn=");
	ft_putendl(str);
	while (ft_isalnum(str[j + *i]) || str[j + *i] == '_')
		j++;
	name = ft_strsub(str, *i , j);
	nb = my_get_var(sh, name);
	free(name);
	name = NULL;
	l_tmp = *list_var;
	if (l_tmp)
	{
			while (l_tmp->next)
				l_tmp = l_tmp->next;
			l_tmp->next = (t_list_ari*)malloc(sizeof(t_list_ari));
			l_tmp->next->var = ft_strdup(nb);
			l_tmp->next->name = ft_strsub(str, *i, j);
			l_tmp->next->next = NULL;
			l_tmp->next->nbr = ft_atoi(nb);
			l_tmp->next->opt = ft_var_modif(str, *i, j, l_tmp);
			if (l_tmp->next->opt == 1 || l_tmp->next->opt == 2)
			{
				free(nb);
				nb = NULL;
				nb = ft_strdup(l_tmp->next->var);
			}
	}
	else
	{
			*list_var = (t_list_ari*)malloc(sizeof(t_list_ari));
			(*list_var)->var = ft_strdup(nb);
			(*list_var)->name = ft_strsub(str, *i, j);
			(*list_var)->next = NULL;
			(*list_var)->nbr = ft_atoi(nb);
			(*list_var)->opt = ft_var_modif(str, *i, j, *list_var);
 			if ((*list_var)->opt == 1 || (*list_var)->opt == 2)
			{
				free(nb);
				nb = NULL;
				nb = ft_strdup((*list_var)->var);
			}
	}
	tmp = ft_strjoin(nb, &str[j + *i]);
	free(nb);
	nb = NULL;
	nb = ft_strsub(str, 0, *i);
	new = ft_strjoin(nb,tmp);
	free(tmp);
	tmp = NULL;
	free(nb);
	nb = NULL;
	free(str);
	str = NULL;
	*i = *i + j;
	return (new);
}

char 			*ft_check_var(char *str, t_list_ari **list_var, t_42sh *sh)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if ((ft_isalpha(str[i])) || (str[i] == '_'))
			str = ft_replace_var(str, list_var, &i, sh);
		else
			i++;
	}
	return (str);
}
