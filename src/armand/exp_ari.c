/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:18:14 by achavy            #+#    #+#             */
/*   Updated: 2019/04/11 04:31:17 by achavy           ###   ########.fr       */
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
	end = ft_strdup(&str[size]);
	tmp = ft_strsub(str, 0, size);
	free(str);
	str = NULL;
	str = tmp;
	tmp = NULL;
	while (i < size)
	{
		if (str[i] == ')' && p == -1)
		{

			ft_putendl_fd("parenthese error", 2);
			return (NULL);
		}
		if (str[i] == '(')
			p = i;
		if (p != -1 && str[i] == ')')
		{
			ft_resolve(&str[p + 1], i - p - 1);
			str[p] = ' ';
			str[i] = ' ';
			p = -1;
			i = -1;
			str = ft_erase_space(str);
			size = ft_strlen(str);
		}
		i++;
	}
	if (p != -1)
	{
		ft_putendl_fd("parenthese error", 2);
		return (NULL);
	}
	ft_resolve(str, size);
	return (str);
}

/*static void		ft_replace_var(t_list_ari *tmp, t_42sh *sh)
{
		

}*/

void			ft_modif_var(t_list_ari *list_var, t_42sh *sh)
{
	t_list_ari *tmp;
	
	tmp = list_var;
	while (tmp)
	{
		ft_putendl(tmp->name);
		ft_putnbr(tmp);
		ft_putchar('\n');
		free(tmp->name);
		free(tmp->var);
		list_var = tmp;
		tmp = tmp->next;
		free(list_var);
	}
}

char		*exp(char *str, t_42sh *sh)
{
	t_list_ari	*list_var;

	if (!str)
		return (ft_itoa(0));
	list_var = NULL;
	if (!(str = ft_check_var(&str, &list_var, sh)))
		return (NULL);
	if (!(ft_check_exp_ari(str)))
		return (NULL);
	str = ft_erase_space(str);
	if (!(str = ft_exp_ari(str, ft_strlen(str))))
		return (NULL);
	ft_putendl(str);
	ft_modif_var(list_var);
	return (str);
}
