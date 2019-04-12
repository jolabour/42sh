/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_brace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:20:56 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:21:07 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_exp_brace_error(t_txtlist *txt)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	write(STDERR_FILENO, txt->data + txt->start, txt->len);
	ft_putstr_fd(": bad substitution\n", STDERR_FILENO);
	return (-1);
}

int				ft_exp_brace(t_txtlist *txt, t_42sh *shell)
{
	t_expparam	expparam;
	int			i;

	ft_bzero(&expparam, sizeof(t_expparam));
	i = 2;
	i = i + ft_expparam_getvar(txt->data + txt->start + i, &expparam);
	i = i + ft_expparam_getfunc(txt->data + txt->start + i, &expparam);
	expparam.word = ft_strsub(txt->data, txt->start + i, txt->len - i - 1);
	return (expparam.f(txt, shell, &expparam));
}
