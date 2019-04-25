/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 07:39:46 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/25 03:34:54 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char			*check_cd_path(t_42sh *sh, char *curpath, int j)
{
	char		*path;
	char		*tmp;

	if (sh->cd_path[j + 1] == NULL)
		sh->cd_err = 1;
	if (ft_strequ(".", sh->cd_path[j]) == 1
			|| ft_strequ("./", sh->cd_path[j]) == 1)
	{
		ft_strdel(&sh->cd_path[j]);
		sh->cd_path[j] = ft_strdup(sh->pwd);
	}
	tmp = ft_strjoin("/", curpath);
	path = ft_strjoin(sh->cd_path[j], tmp);
	free(tmp);
	return (path);
}

char			*get_path_cd(char *curpath, t_42sh *sh, int j)
{
	char		*path;

	if (curpath && curpath[0] != '/')
		path = check_cd_path(sh, curpath, j);
	else
		path = ft_strdup(curpath);
	return (path);
}

void			exec_cd_path(char *curpath, t_42sh *sh, int opt, int i)
{
	char		*path;
	int			j;

	j = -1;
	while (sh->cd_path[++j])
	{
		path = get_path_cd(curpath, sh, j);
		if (opt == 2)
			get_path(path, sh, i);
		else
		{
			if (check_path_opt(curpath, sh, i) == 1)
			{
				sh->path_cd = ft_strdup(path);
				break ;
			}
		}
		ft_strdel(&path);
		if (sh->cd_err == 2)
			return ;
		if (sh->cd_err == 3)
			break ;
	}
	free(path);
	get_dir_cd(sh->path_cd, sh, opt, i);
}

char			*check_arg_cd(char *str, t_42sh *sh)
{
	char		*old_pwd;
	char		*home;
	char		*curpath;

	if (str && (ft_strequ(str, "-") == 1))
	{
		sh->print_pwd = true;
		if ((old_pwd = getenv_cd(sh->copy_env, "OLDPWD=", 7, sh->var)) == NULL)
		{
			ft_putendl_fd("OLDPWD not set.", 2);
			return (NULL);
		}
		return ((curpath = ft_strdup(old_pwd)));
	}
	else if (!str)
	{
		if ((home = getenv_cd(sh->copy_env, "HOME=", 5, sh->var)) == NULL)
		{
			ft_putendl_fd("HOME unset.", 2);
			return (NULL);
		}
		return ((curpath = ft_strdup(home)));
	}
	else
		return ((curpath = ft_strdup(str)));
}

char			*cd_exec(t_42sh *sh, int i)
{
	char		*curpath;

	if (sh->cd_path)
		ft_free_split(sh->cd_path);
	sh->cd_path = ft_strsplit_path(getenv_cd(sh->copy_env,
				"CDPATH=", 7, sh->var), ':');
	sh->print_pwd = false;
	if ((curpath = check_arg_cd(sh->argv->argv[i], sh)) == NULL)
		return (NULL);
	if (ft_strlen(curpath) >= 2)
	{
		if ((ft_strlen(curpath) == 2 && curpath[0] == '.' && curpath[1] == '.')
			|| (curpath[0] == '.' && curpath[1] == '.' && curpath[2] == '/'))
		{
			ft_free_split(sh->cd_path);
			sh->cd_path = ft_strsplit_path(NULL, ':');
		}
	}
	return (curpath);
}
