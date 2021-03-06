/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hashtable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 04:30:08 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/25 05:07:05 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		hash_current_dir(t_ht *ht, DIR *dirp, char *bin_path)
{
	struct dirent	*de;
	char			*path;

	while ((de = readdir(dirp)) != NULL)
	{
		path = ft_joinpath(bin_path, de->d_name);
		if (de->d_type == DT_REG
				&& access(path, X_OK) == 0
				&& (ft_strcmp(de->d_name, ".") != 0)
				&& (ft_strcmp(de->d_name, "..") != 0))
		{
			ht_insert(path, de->d_name, ht);
		}
		free(path);
	}
}

void		init_hashtable(t_42sh *sh)
{
	int		i;
	DIR		*dirp;
	char	*path;

	i = 0;
	ft_memset(&sh->hashtable, 0, sizeof(sh->hashtable));
	if (sh->bin_dirs == NULL)
		return ;
	while ((path = sh->bin_dirs[i++]) != NULL)
	{
		if ((dirp = opendir(path)) == NULL)
			continue ;
		hash_current_dir(&sh->hashtable, dirp, path);
		if (closedir(dirp) == -1)
			return ;
	}
}

void		print_hashtable(t_ht ht)
{
	uint16_t		i;
	BUCKET_CONTENT	*bucket;
	int				used;

	used = 0;
	i = 0;
	while (i < INITIAL_HASHTABLE_SIZE)
	{
		if (ht.buckets[i].first != NULL)
		{
			used++;
			bucket = ht.buckets[i].first;
			while (bucket)
			{
				ft_putstr(bucket->name);
				ft_putstr("=");
				ft_putendl(bucket->path);
				bucket = bucket->next;
			}
		}
		++i;
	}
	if (used == 0)
		ft_putendl("hash table empty");
}
