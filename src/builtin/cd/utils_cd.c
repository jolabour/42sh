/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 07:35:59 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/25 03:20:37 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char			*getenv_cd(char **env, const char *name, size_t len,
		t_var_mark *var)
{
	t_var	*tmp;
	int		i;

	if (len < 1)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], name, len) == 0)
			return (env[i] + len);
	}
	if (!var)
		return (NULL);
	tmp = var->begin;
	while (tmp)
	{
		if (ft_strnequ(tmp->to_sub, name, len - 1) == 1)
			return (tmp->sub);
		tmp = tmp->next;
	}
	return (NULL);
}

int				check_path_opt(char *str, t_42sh *sh, int i)
{
	DIR			*dir;

	if ((dir = opendir(str)) == NULL)
	{
		if (sh->argv->argv[i] && sh->cd_err == 1)
		{
			if ((sh->argv->argv[i][0] == '/' || sh->cd_err == 1)
				&& sh->argv->argv[i])
			{
				ft_putstr_fd("42sh: cd: ", 2);
				ft_putstr_fd(sh->argv->argv[i], 2);
			}
			else
			{
				ft_putstr_fd("42sh: cd: ", 2);
				ft_putstr_fd(getenv_cd(sh->copy_env, "HOME=", 5, sh->var), 2);
			}
			ft_putendl_fd(": No such file or directory", 2);
			sh->retval = 1;
			sh->cd_err = 2;
		}
		return (0);
	}
	closedir(dir);
	return (1);
}

void			del_all_path(t_path_mark *path)
{
	t_path		*tmp;

	while (path->size > 0)
	{
		tmp = path->begin;
		path->begin = path->begin->next;
		ft_strdel(&tmp->str);
		free(tmp);
		path->size--;
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

void			print_error_cd(char *curpath, t_42sh *sh)
{
	ft_putstr_fd("cd: ", 2);
	if (curpath == NULL)
		ft_putstr_fd(getenv_cd(sh->copy_env, "HOME=", 5, sh->var), 2);
	else
		ft_putstr_fd(curpath, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
