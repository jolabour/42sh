/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:18:14 by achavy            #+#    #+#             */
/*   Updated: 2019/03/26 11:56:34 by achavy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void		ft_resolve(char *str, int size)
{
	char *tmp;

	tmp = NULL;
	if (!(tmp = ft_strsub(str, 0, size)))
		ft_exp_ari_error("malloc error");
	if (!(tmp = ft_math_op(tmp, size)))
		ft_exp_ari_error("malloc error");
	ft_itoa_exp_ari(str, ft_atoi(tmp), size);
	ft_strdel(&tmp);
}

static int	end_ari(char *str)
{
	int	j;
	int i;

	i = 2;
	j = 2;
	while (j != 0)
	{
		if (str[i] == '(')
			j++;
		if (str[i] == ')')
			j--;
		i++;
		if (str[i] == '\0')
			return (0);
	}
	return (i);
}

char		*ft_exp_ari(char *str, int size)
{
	char 	*tmp;
	char	*end;
	int		i;
	int		p;

	i = 0;
	p = -1;
	end = NULL;
	tmp = NULL;
	size = end_ari(str);
	if (!(end = ft_strdup(&str[size])))
		return (NULL);
	if (!(tmp = ft_strsub(str, 0, size)))
		return (NULL);
	free(str);
	str = NULL;
	str = tmp;
	tmp = NULL;
	while (i < size)
	{
		if (str[i] == ')' && p == -1)
			ft_exp_ari_error("parenthese error");
		if (str[i] == '(')
			p = i;
		if (p != -1 && str[i] == ')')
		{
			ft_resolve(&str[p + 1], i - p - 1);
			str[p] = ' ';
			str[i] = ' ';
			p = -1;
			i = -1;
			if (!(str = ft_erase_space(str)))
				ft_exp_ari_error("malloc error");
			size = ft_strlen(str);
		}
		i++;
	}
	if (p != -1)
		ft_exp_ari_error("parenthese error");
	ft_resolve(str, size);
	if (!(tmp = ft_strjoin(str, end)))
		return (NULL);
	free(str);
	str = NULL;
	end = NULL;
	return (tmp);
}

void		ft_modif_var(t_list_ari *list_var)
{
	t_list_ari *tmp;
	
	tmp = list_var;
	/*if (tmp)
	{
		ft_putendl(tmp->name);
		if (tmp->opt == 3)
			ft_putnbr(nbr + 1);
		else if (tmp->opt == 4)
			ft_putnbr(nbr - 1);
		else
			ft_putnbr(nbr);
		ft_putchar('\n');
	}*/
	while (tmp)
	{
		ft_putendl(tmp->name);
		if (tmp->opt == 3)
			ft_putnbr(tmp->nbr + 1);
		else if (tmp->opt == 4)
			ft_putnbr(tmp->nbr - 1);
		else
			ft_putnbr(tmp->nbr);
		ft_putchar('\n');
		free(tmp->name);
		free(tmp->var);
		list_var = tmp;
		tmp = tmp->next;
		free(list_var);
	}
}

/*int				exp(int c, char **v)
{
	t_list_ari	*list_var;
	char		*str;

	str = NULL;
	list_var = NULL;
	if (c == 2)
	{
		if (!(str = ft_strdup(v[1])))
			return (0);
		if (!(str = ft_check_var(str, list_var)))
			return (0);
		ft_check_exp_ari(str);
		if (!(str = ft_erase_space(str)))
			ft_exp_ari_error("malloc error");
		str = ft_exp_ari(str, ft_strlen(str));
		ft_putendl(str);
		ft_modif_var(list_var);
	}
	exit(0);
}*/
