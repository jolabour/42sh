/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 05:38:57 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/27 05:57:41 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		print_type_alias(t_42sh *sh, int i, char *str)
{
	ft_putstr(sh->argv->argv[i]);
	ft_putstr(" is an alias for ");
	ft_putendl(str);
	sh->retval = 0;
}

void		print_type_builtin(t_42sh *sh, int i)
{
	ft_putstr(sh->argv->argv[i]);
	ft_putendl(" is a shell builtin");
	sh->retval = 0;
}

void		print_type_binary(t_42sh *sh, int i, char *str)
{
	ft_putstr(sh->argv->argv[i]);
	ft_putstr(" is ");
	ft_putendl(str);
	sh->retval = 0;
}

void		print_type_hash(t_42sh *sh, int i, char *str)
{
	ft_putstr(sh->argv->argv[i]);
	ft_putstr(" is hashed (");
	ft_putstr(str);
	ft_putendl(")");
	sh->retval = 0;
}

void		print_type_error(t_42sh *sh, int i)
{
	ft_putstr_fd("42sh: type: ", 2);
	ft_putstr_fd(sh->argv->argv[i], 2);
	ft_putendl_fd(": not found", 2);
	if (sh->retval != 0)
		sh->retval = 1;
}
