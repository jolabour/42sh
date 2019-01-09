/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 07:21:16 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/17 02:22:24 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <unistd.h>
#include <curses.h>
#include <term.h>

void		get_term(t_42sh *sh)
{
	//if (tgetent(NULL, ft_getenv(sh->env, "TERM=", 5)) == -1)
	if (tgetent(NULL, getenv("TERM")) == -1)
	{
		ft_putendl("Set term or a valide term.");
		exit(0);
	}
	if (tcgetattr(0, &sh->term) == -1)
	{
		ft_putendl("tcgetattr: Error.");
		exit(0);
	}
	/*if (tgetflag("os") != 1)
	{
		ft_putendl("ah");
	}*/
	sh->term.c_lflag &= ~(ICANON);
	sh->term.c_lflag &= ~(ECHO);
	sh->term.c_lflag &= ~(ISIG);
	if (tcsetattr(0, TCSANOW, &sh->term) == -1)
	{
		ft_putendl("tcsetattr: Error.");
		exit(0);
	}
}

void		init_shell(t_42sh *sh, char **env)
{
	char *path;
	char *pwd;

	sh->env = set_list(env);
	path = ft_getenv(sh->env, "PATH=", sizeof("PATH=") - 1);
	if (path)
	{
		if ((sh->bin_dirs = ft_strsplit(path, ':')) == NULL)
			print_error(_ENOMEM, 1);
	}
	pwd = ft_getenv(sh->env, "PWD=", sizeof("PWD=") - 1);
	if (pwd)
	{
		if ((sh->pwd = ft_strdup(pwd)) == NULL)
			print_error(_ENOMEM, 1);
	}
	sh->copy_env = list_to_tab(sh->env, sh->copy_env);
	sh->path_history = ft_strdup(".42sh_history");
	sh->lexer = NULL;
	init_hashtable(sh);
	get_term(sh);
}
