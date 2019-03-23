/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:18:14 by achavy            #+#    #+#             */
/*   Updated: 2019/02/18 23:41:08 by achavy           ###   ########.fr       */
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
			ft_putendl("++*");	
			str[i - 1] = ' ';
			str[i - 2] = ' ';
			new->nbr = new->nbr + 1;
			free(new->var);
			new->var = NULL;
			if (!(new->var = ft_itoa(new->nbr)))
				return (0); // malloc error
			return (1);
		}
		if (str[i - 1] == '-' && str[i - 2] == '-')
		{
			ft_putendl("--*");
			str[i - 1] = ' ';
			str[i - 2] = ' ';
			new->nbr = new->nbr - 1;
			free(new->var);
			new->var = NULL; 
			if (!(new->var = ft_itoa(new->nbr)))
				return (0); // malloc error
			return (2);
		}
	}
	if (j + 1 <= len)
	{
//		ft_putendl("pas bon");
//		ft_putendl(&str[j]);
		if (str[j] == '+' && str[j + 1] == '+')
		{
			ft_putendl("*++");
			str[j] = ' ';
			str[j + 1] = ' ';
			return (3);
		}
		if (str[j] == '-' && str[j + 1] == '-')
		{
			ft_putendl("*--");
			str[j] = ' ';
			str[j + 1] = ' ';
			return (4);
		}
	}
	return (0);
}

static char		*ft_replace_var(char *str, t_list_ari *list_var, int *i, int a)
{
	t_list_ari	*l_tmp;	
	char		*tmp;
	char 		*new;
	char		*nb;
	int			j;

	j = 0;
	nb = NULL;
	new = NULL;
	tmp = NULL;
	l_tmp = NULL;
	while (ft_isalpha(str[j + *i]))	
		j++;
	ft_putstr("give me : ");
	write(1, &str[*i], j);
	ft_putstr(" : ");
	get_next_line(0, &nb);
	if (!nb)
		return (0);
	ft_putendl(nb);
	l_tmp = list_var;
	if (a != 0)
	{
		if (list_var)
		{
			while (l_tmp->next)
				l_tmp = l_tmp->next;
			if ((!(l_tmp->next = (t_list_ari*)malloc(sizeof(t_list_ari))))
			|| (!(l_tmp->next->var = ft_strdup(nb)))
			|| (!(l_tmp->next->name = ft_strsub(str, *i, j))))
				return (0);
			l_tmp->next->next = NULL;
			l_tmp->next->nbr = ft_atoi(nb);
			l_tmp->next->opt = ft_var_modif(str, *i, j, l_tmp);
			if (l_tmp->next->opt == 1 || l_tmp->next->opt == 2)
			{
				free(nb);
				nb = NULL;
				if (!(nb = ft_strdup(l_tmp->next->var)))
					return (0);
			}
		}
		else
		{
			if ((!(list_var = (t_list_ari*)malloc(sizeof(t_list_ari))))
			|| (!(list_var->var = ft_strdup(nb)))
			|| (!(list_var->name = ft_strsub(str, *i, j))))
				return (0);
			list_var->next = NULL;
			list_var->nbr = ft_atoi(nb);
			list_var->opt = ft_var_modif(str, *i, j, list_var);
 			if (list_var->opt == 1 || list_var->opt == 2)
			{
				free(nb);
				nb = NULL;
				if (!(nb = ft_strdup(list_var->var)))
					return (0);
			}
		}
	}
	if (!(tmp = ft_strjoin(nb, &str[j + *i])))
		return (0);
ft_putendl(tmp);
	free(nb);
	nb = NULL;
	if ((!(nb = ft_strsub(str, 0, *i)))
	|| (!(new = ft_strjoin(nb,tmp))))
		return (0);
ft_putendl(nb);
ft_putendl(new);
	free(tmp);
	tmp = NULL;
	free(nb);
	nb = NULL;
	free(str);
	str = NULL;
	get_next_line(-2, NULL);	
	*i = *i + j;
	return (new);
}

char 			*ft_check_var(char *str, t_list_ari *list_var)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && ft_isalpha(str[i + 1]))
		{
			str[i] = ' ';
			i++;
			str = ft_replace_var(str, list_var, &i, 0);
			if (!str)
				return (NULL);
		}
		if (ft_isalpha(str[i]))
		{
			str = ft_replace_var(str, list_var, &i, 1);
			if (!str)
				return (NULL);
		}
		i++;
	}
	ft_putchar('C');
	ft_putendl(str);
	return (str);
}
