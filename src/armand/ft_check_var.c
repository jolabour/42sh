/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:18:14 by achavy            #+#    #+#             */
/*   Updated: 2019/04/20 03:46:56 by achavy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** 1=++* 2=--* 3=*++ 4=*--
*/

static int			ft_check_before_inc(char *str, int i, t_list_ari *new)
{
	if (str[i - 1] == '+' && str[i - 2] == '+')
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
	return (0);
}

int					ft_var_modif(char *str, int i, int j, t_list_ari *new)
{
	int		ret;
	int		len;

	len = ft_strlen(str);
	ret = 0;
	if (i > 1)
		if ((ret = ft_check_before_inc(str, i, new)))
			return (ret);
	if (i + j + 1 <= len)
	{
		if (str[i + j] == '+' && str[i + j + 1] == '+')
		{
			str[i + j] = ' ';
			str[i + j + 1] = ' ';
			return (3);
		}
		if (str[i + j] == '-' && str[i + j + 1] == '-')
		{
			str[i + j] = ' ';
			str[i + j + 1] = ' ';
			return (4);
		}
	}
	return (0);
}

static void			ft_end_replace_exp(char *str, size_t *i, int j
, char **tabb)
{
	tabb[0] = ft_strjoin(tabb[2], &str[j + *i]);
	ft_strdel(&tabb[2]);
	tabb[2] = ft_strsub(str, 0, *i);
	tabb[1] = ft_strjoin(tabb[2], tabb[0]);
	ft_strdel(&tabb[0]);
	free(tabb[2]);
	free(str);
	str = NULL;
}

static char			*ft_replace_var(char *str, t_list_ari **list_var,
size_t *i, t_42sh *sh)
{
	t_list_ari	*l_tmp;
	char		*tabb[4];
	int			j;
	int			t;

	j = 1;
	while (ft_isalnum(str[j + *i]) || str[j + *i] == '_')
		j++;
	tabb[3] = ft_strsub(str, *i, j);
	tabb[2] = my_get_var(sh, tabb[3]);
	t = ft_strlen(tabb[2]);
	ft_strdel(&tabb[3]);
	l_tmp = *list_var;
	if (l_tmp)
	{
		while (l_tmp->next)
			l_tmp = l_tmp->next;
		l_tmp->next = ft_add_var_exp(str, i, j, &tabb[2]);
	}
	else
		*list_var = ft_add_var_exp(str, i, j, &tabb[2]);
	ft_end_replace_exp(str, i, j, tabb);
	*i = *i + t;
	return (tabb[1]);
}

char				*ft_check_var(char *str, t_list_ari **list_var, t_42sh *sh)
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
