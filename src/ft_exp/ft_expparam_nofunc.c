/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expparam_nofunc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:19:54 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:20:01 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_expparam_nofunc(t_txtlist *txt, t_42sh *shell,
				t_expparam *expparam)
{
	if (!expparam->param || expparam->word[0])
	{
		ft_expparam_free(expparam);
		return (ft_exp_brace_error(txt));
	}
	txt->data = ft_getvar(expparam->param, shell);
	txt->data = txt->data ? ft_backslash_quotes(txt->data, txt->dquote)
		: ft_strdup("");
	ft_expparam_free(expparam);
	return (0);
}
