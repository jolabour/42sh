/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:18:14 by achavy            #+#    #+#             */
/*   Updated: 2019/04/20 02:42:38 by achavy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void		ft_resolve(char *str, int size)
{
	char *tmp;

	tmp = NULL;
	tmp = ft_strsub(str, 0, size);
	tmp = ft_math_op(tmp, size);
	ft_itoa_exp_ari(str, ft_atoi(tmp), size);
	ft_strdel(&tmp);
}

static char		*ft_exp_parenthese(char *str, int *i, int *p, int *size)
{
	if (str[*i] == ')' && *p == -1)
	{
		free(str);
		ft_putendl_fd("42sh: parenthese error", 2);
		return (NULL);
	}
	if (str[*i] == '(')
		*p = *i;
	if (*p != -1 && str[*i] == ')')
	{
		ft_resolve(&str[*p + 1], *i - *p - 1);
		str[*p] = ' ';
		str[*i] = ' ';
		*p = -1;
		*i = -1;
		str = ft_erase_space(str);
		*size = ft_strlen(str);
	}
	*i = *i + 1;
	return (str);
}

static char		*ft_exp_ari(char *str, int size)
{
	int		i;
	int		p;

	i = 0;
	p = -1;
	while (i < size)
	{
		if (!(str = ft_exp_parenthese(str, &i, &p, &size)))
			return (NULL);
	}
	if (p != -1)
	{
		free(str);
		ft_putendl_fd("42sh: parenthese error", 2);
		return (NULL);
	}
	ft_resolve(str, size);
	return (str);
}

void			ft_modif_var(t_list_ari *list_var, t_42sh *sh)
{
	t_list_ari *tmp;

	tmp = list_var;
	while (tmp)
	{
		if ((tmp->opt == 3) || (tmp->opt == 4))
		{
			if (tmp->opt == 3)
				tmp->nbr = tmp->nbr + 1;
			else
				tmp->nbr = tmp->nbr - 1;
			free(tmp->var);
			tmp->var = NULL;
			tmp->var = ft_itoa(tmp->nbr);
		}
		ft_replace_vari(tmp, sh);
		free(tmp->name);
		free(tmp->var);
		list_var = tmp;
		tmp = tmp->next;
		free(list_var);
	}
}

char			*ft_exp_ary(char *str, t_42sh *sh)
{
	t_list_ari	*list_var;

	if (!str)
		return (ft_itoa(0));
	list_var = NULL;
	if (!(str = ft_check_var(str, &list_var, sh)))
	{
		ft_free_ari(list_var, str);
		return (NULL);
	}
	if (!(ft_check_exp_ari(str)))
	{
		ft_free_ari(list_var, str);
		return (NULL);
	}
	str = ft_erase_space(str);
	if (!(str = ft_exp_ari(str, ft_strlen(str))))
	{
		ft_free_ari(list_var, str);
		return (NULL);
	}
	ft_modif_var(list_var, sh);
	return (str);
}
