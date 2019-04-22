/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 00:37:39 by abeauvoi          #+#    #+#             */
/*   Updated: 2019/04/20 03:49:49 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "sh.h"

void		get_path(char *path, t_42sh *sh, int i)
{
	char	*tmp;
	char	*real_path;
	char	*tmp2;

	if (check_path_opt(path, sh, i) == 0)
		return ;
	if (path[0] != '/')
	{
		tmp = ft_strdup(sh->pwd);
		tmp2 = ft_strjoin("/", path);
		real_path = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
	}
	else
		real_path = ft_strdup(path);
	get_list(real_path, sh);
	ft_dot_dot(sh, &sh->path->begin);
	if (sh->path->size == 0)
		sh->path_cd = ft_strdup("/");
	else
		join_all(sh);
	del_all_path(sh->path);
	free(real_path);
	sh->cd_err = 3;
}

void		get_pwd(t_42sh *sh)
{
	char	*str;

	str = ft_strjoin("OLDPWD=", sh->pwd);
	check_local_variable(sh, str);
	free(str);
}

void		get_dir_cd(char *curpath, t_42sh *sh, int opt, int i)
{
	char	*str;
	char	cwd[4096];

	if (curpath == NULL)
		print_error_cd(sh->argv->argv[i]);
	if (chdir(curpath) == -1)
		print_error_cd(sh->argv->argv[i]);
	else
	{
		if (sh->pwd)
			get_pwd(sh);
		if (opt == 2)
			str = ft_strjoin("PWD=", curpath);
		else
			str = ft_strjoin("PWD=", getcwd(cwd, 4095));
		check_local_variable(sh, str);
		free(sh->pwd);
		sh->pwd = ft_strdup(str + 4);
		free(str);
	}
	if (sh->print_pwd)
		ft_putendl(sh->pwd);
	ft_strdel(&sh->path_cd);
}

void		builtin_cd(t_42sh *sh)
{
	int		opt;
	int		i;
	char	*curpath;

	i = 1;
	sh->retval = 0;
	sh->cd_err = 0;
	opt = check_opt_cd(sh, &i);
	if ((curpath = cd_exec(sh, i)) == NULL)
		return ;
	exec_cd_path(curpath, sh, opt, i);
	free(curpath);
}
