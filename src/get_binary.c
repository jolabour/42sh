/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 04:30:08 by jolabour          #+#    #+#             */
/*   Updated: 2018/08/25 06:27:08 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <dirent.h>

void		read_current_dir(DIR *dirp, char *path)
{
	struct dirent	*de;
	char			*real_path;

	while ((de = readdir(dirp)) != NULL)
	{
		real_path = ft_strjoin(path, de->d_name);
		if (access(real_path, X_OK) && (ft_strcmp(de->d_name, ".") != 0) && (ft_strcmp(de->d_name, "..") != 0))
		{
			//	tabhash[fonctionhash(de->d_name)];
			ft_putendl(de->d_name);
		}
	}
}

void		open_dir(char *path)
{
	DIR		*dirp;

	if (!(dirp = opendir(path)))
		return ;
	read_current_dir(dirp, path);
	if (closedir(dirp) == -1)
		return ;
}

void		get_binary(t_42sh *sh)
{
	int		i;

	i = 0;
	while (sh->bin_dirs[i] != 0)
	{
		open_dir(sh->bin_dirs[i]);
		i++;
	}
}
