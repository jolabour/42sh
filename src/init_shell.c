/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 07:21:16 by jolabour          #+#    #+#             */
/*   Updated: 2018/07/29 07:31:33 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		init_shell(t_42sh *sh, char **env)
{
	char *path;
	char *pwd;

	sh->env = set_list(env);
	path = ft_getenv(sh->env, "PATH=", sizeof("PATH=") - 1);
	if (path)
	{
		if (!(sh->bin_dirs = ft_strsplit(path, ':')))
			print_error_and_exit(_ENOMEM);
	}
	pwd = ft_getenv(sh->env, "PWD=", sizeof("PWD=") - 1);
	if (pwd)
	{
		if (!(sh->pwd = ft_strdup(pwd)))
			print_error_and_exit(_ENOMEM);
	}
	list_to_tab(sh->env, sh->copy_env);
}
