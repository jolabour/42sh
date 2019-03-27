/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 05:58:49 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/27 06:01:08 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		list_del(t_env **env, t_env *to_del, t_env *prev)
{
	if (*env == to_del)
		*env = to_del->next;
	else
		prev->next = to_del->next;
	free(to_del->str);
	free(to_del);
}

void		lst_del_var(t_var **var, t_var *to_del, t_var *prev)
{
	if (*var == to_del)
		*var = to_del->next;
	else
		prev->next = to_del->next;
	free(to_del->sub);
	free(to_del->to_sub);
	free(to_del);
}
