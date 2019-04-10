/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 06:02:54 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/10 08:11:55 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <curses.h>
#include <term.h>

void		init_builtin_tab(t_42sh *sh)
{
	sh->builtin = (char**)ft_malloc_exit(sizeof(char *) * 13);
	sh->builtin[0] = "echo";
	sh->builtin[1] = "cd";
	sh->builtin[2] = "type";
	sh->builtin[3] = "alias";
	sh->builtin[4] = "unalias";
	sh->builtin[5] = "exit";
	sh->builtin[6] = "test";
	sh->builtin[7] = "fc";
	sh->builtin[8] = "hash";
	sh->builtin[9] = "set";
	sh->builtin[10] = "unset";
	sh->builtin[11] = "export";
	sh->builtin[12] = NULL;
}

void		get_term(t_42sh *sh)
{
	if (tgetent(NULL, getenv("TERM")) == -1)
	{
		ft_putendl("Set term or a valide term.");
		exit(0);
	}
	if (tcgetattr(0, &sh->reset_term) == -1)
	{
		ft_putendl("tcgetattr: Error.");
		exit(0);
	}
	if (tcgetattr(0, &sh->term) == -1)
	{
		ft_putendl("tcgetattr: Error.");
		exit(0);
	}
	sh->term.c_lflag &= ~(ICANON);
	sh->term.c_lflag &= ~(ECHO);
	sh->term.c_lflag &= ~(ISIG);
	if (tcsetattr(0, TCSANOW, &sh->term) == -1)
	{
		ft_putendl("tcsetattr: Error.");
		exit(0);
	}
}

void		reset_term(t_42sh *sh)
{
	if (tcsetattr(0, TCSANOW, &sh->reset_term) == -1)
	{
		ft_putendl("tcsetattr: Error.");
		exit(0);
	}
}

void		init_alias_list(t_42sh *sh)
{
	sh->alias = (t_alias_mark*)ft_malloc_exit(sizeof(t_alias_mark));
	sh->alias->size = 0;
}

void		init_shell(t_42sh *sh, char **env)
{
	char	*path;
	char	*pwd;

	sh->env = set_list(env);
	sh->var = (t_var_mark*)ft_malloc_exit(sizeof(t_var_mark));
	sh->var->size = 0;
	path = ft_getenv(sh->env, "PATH=", sizeof("PATH=") - 1, sh->var);
	if (path)
		sh->bin_dirs = ft_strsplit(path, ':');
	pwd = ft_getenv(sh->env, "PWD=", sizeof("PWD=") - 1, sh->var);
	if (pwd)
		sh->pwd = ft_strdup(pwd);
	sh->copy_env = list_to_tab(sh->env, sh->copy_env);
	sh->path_history = ft_strdup(".42sh_history");
	init_builtin_tab(sh);
	sh->line_to_replace = NULL;
	sh->argv = NULL;
	sh->argv = (t_argv*)ft_malloc_exit(sizeof(t_argv));
	sh->argv->error_code = 0;
	sh->argv->argv = NULL;
	init_alias_list(sh);
	sh->path = ft_malloc_exit(sizeof(t_path_mark));
	init_hashtable(sh);
	get_term(sh);
}
