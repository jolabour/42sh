/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exp_ari.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 02:19:40 by achavy            #+#    #+#             */
/*   Updated: 2019/04/25 03:53:23 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char			*my_get_var(t_42sh *sh, char *name)
{
	char	*str;
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	str = ft_strjoin(name, "=");
	if ((ret = ft_getenv(sh->env, str, ft_strlen(str), sh->var)))
	{
		free(str);
		return (ft_strdup(ret));
	}
	free(str);
	return (ft_strdup("0"));
}

t_list_ari		*ft_add_var_exp(char *str, size_t *i, int j, char **nb)
{
	t_list_ari	*new;

	new = NULL;
	new = (t_list_ari*)ft_malloc_exit(sizeof(t_list_ari));
	new->var = ft_strdup(*nb);
	new->name = ft_strsub(str, *i, j);
	new->next = NULL;
	new->nbr = ft_atoi(*nb);
	new->opt = ft_var_modif(str, *i, j, new);
	if (new->opt == 1 || new->opt == 2)
	{
		free(*nb);
		*nb = NULL;
		*nb = ft_strdup(new->var);
	}
	return (new);
}

void			ft_replace_vari(t_list_ari *tmp, t_42sh *sh)
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

void			ft_free_ari(t_list_ari *list, char *str)
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
