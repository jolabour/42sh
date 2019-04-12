/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:18:14 by achavy            #+#    #+#             */
/*   Updated: 2019/04/12 04:30:13 by achavy           ###   ########.fr       */
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

/*static int	end_ari(char *str)
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
}*/

static char		*ft_exp_ari(char *str, int size)
{
	int		i;
	int		p;

	i = 0;
	p = -1;
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

static void		ft_replace_var(t_list_ari *tmp, t_42sh *sh)
{
	char	*tmp_str;
	char	*str;

	str = NULL;
	tmp_str = NULL;
	tmp_str = ft_strjoin(tmp->name, "=");
	str = ft_strjoin(tmp_str, tmp->var);
	free(tmp_str);
	check_local_variable(sh, str);
	free(str);
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
				tmp->nbr = tmp->nbr + 1;
			free(tmp->var);
			tmp->var = NULL;
			tmp->var = ft_itoa(tmp->nbr);
		}
		ft_replace_var(tmp, sh);
		free(tmp->name);
		free(tmp->var);
		list_var = tmp;
		tmp = tmp->next;
		free(list_var);
	}
}

static void	ft_free_ari(t_list_ari *list, char *str)
{
	t_list_ari *tmp;

	tmp = list;
	while (tmp)
	{
		free(tmp->var);
		free(tmp->name);
		list = tmp;
		tmp = tmp->next;
		free(list);
	}
	if (str)
		free(str);
}

char		*ft_exp_ary(char *str, t_42sh *sh)
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
//	ft_putendl(str);
	if (!(ft_check_exp_ari(str)))
	{
		ft_free_ari(list_var, str);
		return (NULL);
	}
//	ft_putendl(str);
	str = ft_erase_space(str);
//	ft_putendl(str);
	if (!(str = ft_exp_ari(str, ft_strlen(str))))
	{
		ft_free_ari(list_var, str);
		return (NULL);
	}
//	ft_putendl(str);
	ft_modif_var(list_var, sh);
	return (str);
}
