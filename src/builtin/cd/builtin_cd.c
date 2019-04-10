/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 00:37:39 by abeauvoi          #+#    #+#             */
/*   Updated: 2019/04/10 11:16:27 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "sh.h"

static void		print_error_cd(char *curpath)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(curpath, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

t_path		*create_node_path(char *str)
{
	t_path	*new;

	new = (t_path*)ft_malloc_exit(sizeof(*new));
	new->str = ft_strdup(str);
	new->next = NULL;
	return (new);
}

void		lst_push_path(t_path **head, t_path *new)
{
	t_path	*tmp;

	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_path		*set_list_path(char **split, t_42sh *sh)
{
	t_path	*start;
	t_path	*new;
	int		i;

	start = NULL;
	i = 0;
	while (split[i])
	{
		new = create_node_path(split[i]);
		lst_push_path(&start, new);
		i++;
	}
	sh->path->size = i;
	return (start);
}

void			get_list(char *str, t_42sh *sh)
{
	char		**split;

	split = ft_strsplit_with(str, '/');
	sh->path->begin = set_list_path(split, sh);
}

void	lst_del_path(t_path **path, t_path *to_del, t_path *prev)
{
	if (*path == to_del)
		*path = to_del->next;
	else
		prev->next = to_del->next;
	free(to_del->str);
	free(to_del);
}

void	lst_del_path_dotdot(t_path **path, t_path *to_del, t_path *prev)
{
	if (*path == to_del)
		*path = to_del->next->next;
	else
		prev->next = to_del->next->next;
	free(to_del->str);
	free(to_del->next->str);
	free(to_del->next);
	free(to_del);
}

void			delete_sdot(t_42sh *sh, t_path **path)
{
	t_path		*prev;
	t_path		*tmp;
	int			i;

	tmp = *path;
	i = 0;
	prev = tmp;
	while (i < sh->path->size)
	{
		if (ft_strequ(tmp->str, "/.") == 1)
		{
			lst_del_path(path, tmp, prev);
			sh->path->size--;
			tmp = *path;
			prev = tmp;
			i = 0;
		}
		else
		{
			i++;
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

int				ft_dot_dot(t_42sh *sh, t_path **path)
{
	t_path		*tmp;
	t_path		*prev;
	int			i;

	delete_sdot(sh, path);
	tmp = *path;
	prev = tmp;
	i = 0;
	while (i + 1 < sh->path->size)
	{
		if (ft_strequ(tmp->next->str, "/..") == 1 && ft_strequ(tmp->str, "/..") == 0)
		{
			lst_del_path_dotdot(path, tmp, prev);
			sh->path->size = sh->path->size - 2;
			i = 0;
			tmp = *path;
			prev = tmp;
		}
		else
		{
			i++;
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (1);
}

int				check_path_opt(char *str, t_42sh *sh)
{
//	DIR			*dir;
	//struct stat	info;

	if (access(str, F_OK) != 0)
	{
		ft_putstr_fd("42sh: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directorylolXD", 2);
		sh->retval = 1;
		return (0);
	}
	return (1);/*if (lstat(str, &info) != 0)
	{
		ft_putstr_fd("42sh: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directorylolXD", 2);
		sh->retval = 1;
		return (0);
	}
	if ((S_ISDIR(info.st_mode)) == 1)
		return (1);
	ft_putstr_fd("42sh: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": No such file or directorylol", 2);
	sh->retval = 1;
	return (0);
	if ((dir = opendir(str)) == NULL)
	{
		ft_putstr_fd("42sh: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directorylol", 2);
		sh->retval = 1;
		return (0);
	}
	closedir(dir);*/
}


void			ft_print_path(t_42sh *sh)
{
	t_path		*tmp;
	int			i;

	tmp = sh->path->begin;
	i = 0;
	while (i < sh->path->size)
	{
		ft_putendl(tmp->str);
		i++;
		tmp = tmp->next;
	}
}

void			join_all(t_42sh *sh)
{
	t_path		*tmp_p;
	int			i;
	char		*tmp2;

	tmp_p = sh->path->begin;
	if (ft_strequ(tmp_p->str, "/..") == 1)
	{
		sh->path_cd = ft_strdup("/");
		return ;
	}
	i = 0;
	sh->path_cd = ft_strdup("\0");
	while (i < sh->path->size)
	{
		tmp2 = ft_strdup(sh->path_cd);
		free(sh->path_cd);
		sh->path_cd = ft_strjoin(tmp2, tmp_p->str);
		free(tmp2);
		i++;
		tmp_p = tmp_p->next;
	}
}

int				get_path(char *str, t_42sh *sh)
{
	char		*path;
	char		*tmp;

	if (str[0] != '/')
	{
		tmp = ft_strjoin("/", str);
		path = ft_strjoin(ft_getenv(sh->env, "PWD=", 4, sh->var), tmp);
		free(tmp);
	}
	else
		path = ft_strdup(str);
	check_path_opt(path, sh);
	get_list(path, sh);
	ft_dot_dot(sh, &sh->path->begin);
	if (sh->path->size == 0)
		sh->path_cd = ft_strdup("/");
	else
		join_all(sh);
	ft_print_path(sh);
	free(path);
	return (1);
}

static void		get_dir_cd(char *curpath, t_42sh *sh, bool print_pwd, int opt)
{
	char		*str;
	char		cwd[4096];

	ft_bzero(cwd, 4096);
	if (chdir(curpath) == -1)
		print_error_cd(curpath);
	else
	{
		str = ft_strjoin("OLDPWD=", ft_getenv(sh->env, "PWD=", 4, sh->var));
		check_local_variable(sh, str);
		free(str);
		if (opt == 2)
		{
			str = ft_strjoin("PWD=", curpath);
			check_local_variable(sh, str);
			free(str);
		}
		else
		{
			str = ft_strjoin("PWD=", getcwd(cwd, 4095));
			check_local_variable(sh, str);
			free(str);
		}
	}
	if (print_pwd)
		ft_putendl(ft_getenv(sh->env, "PWD=", 4, sh->var));
}

void			cd_exec(t_42sh *sh, int i, int opt)
{
	bool		print_pwd;
	char		*curpath;

	print_pwd = false;
	if (sh->argv->argv[i] && (ft_strequ(sh->argv->argv[i], "-") == 1))
	{
		print_pwd = true;
		if (!(curpath = ft_strdup(ft_getenv(sh->env, "OLDPWD=", 7, sh->var))))
		{
			ft_putendl_fd("OLDPWD not set.", 2);
			return ; //(0);
		}
	}
	else if (!sh->argv->argv[i])
		curpath = ft_strdup(ft_getenv(sh->env, "HOME=", 5, sh->var));
	else
		curpath = ft_strdup(sh->argv->argv[i]);
	if (curpath == NULL)
	{
		ft_putendl_fd("HOME unset.", 2);
		return ;//(-1);
	}
	if (opt == 2)
	{
		if (get_path(curpath, sh) == 0)
			return ;
	}
	else
		sh->path_cd = ft_strdup(curpath);
	free(curpath);
	get_dir_cd(sh->path_cd, sh, print_pwd, opt);
	return; //(0);
}

int			check_str_opt(char *str, t_42sh *sh)
{
	int		i;
	int		opt;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'L')
			opt = 2;
		else if (str[i] == 'P')
			opt = 1;
		else
		{
			ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", 2);
			sh->retval = 1;
			return ((opt = 0));
		}
		i++;
	}
	return (opt);
}

int			check_opt_cd(t_42sh *sh, int *i)
{
	int		opt;

	opt = 2;
	if (sh->argv->size < 2)
		return (2);
	while (sh->argv->argv[*i])
	{
		if (sh->argv->argv[*i][0] != '-' || ft_strequ(sh->argv->argv[*i], "-") == 1)
			return (opt);
		opt = check_str_opt(sh->argv->argv[*i], sh);
		if (opt == 0)
			return (0);
		*i = *i + 1;
	}
	return (opt);
}

void		builtin_cd(t_42sh *sh)
{
	int		opt;
	int		i;

	i = 1;
	opt = check_opt_cd(sh, &i);
	cd_exec(sh, i, opt);
	//else if (opt == 2)
	//	cd_l(sh);
}

