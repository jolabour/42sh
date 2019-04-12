/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expparam_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:13:31 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:54:12 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_expparam_getvar(char *exp, t_expparam *expparam)
{
	int			i;

	i = 0;
	if (ft_get_spparam(exp[0]))
		expparam->param = ft_strsub(exp, 0,
			(i = 1));
	else if (ft_isalpha(exp[0]) || exp[0] == '_')
	{
		while (ft_isalnum(exp[i]) || exp[i] == '_')
			i++;
		expparam->param = ft_strsub(exp, 0, i);
	}
	return (i);
}

void			ft_expparam_free(t_expparam *expparam)
{
	if (expparam->param)
		free(expparam->param);
	if (expparam->word)
		free(expparam->word);
}

int				ft_expparam_getfunc(char *exp, t_expparam *expparam)
{
	int			i;
	int			op;

	i = 0;
	op = -1;
	while (g_expparamtab[i].str)
	{
		while (g_expparamtab[i].str && !ft_strnequ(g_expparamtab[i].str,
			exp, ft_strlen(g_expparamtab[i].str)))
			i++;
		if (g_expparamtab[i].str && (op == -1
			|| ft_strlen(g_expparamtab[i].str)
			> ft_strlen(g_expparamtab[op].str)))
			op = i;
		if (g_expparamtab[i].str)
			i++;
	}
	expparam->f = g_expparamtab[op].f;
	return (ft_strlen(g_expparamtab[op].str));
}
