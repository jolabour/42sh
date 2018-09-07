/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hashtable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 04:30:08 by jolabour          #+#    #+#             */
/*   Updated: 2018/09/08 00:40:21 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <dirent.h>

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
	while ((path = sh->bin_dirs[i++]) != NULL)
	{
		if ((dirp = opendir(path)) == NULL)
		{
			// print_error;
			continue ;
		}
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

	i = 0;
	used = 0;
	while (i < INITIAL_HASHTABLE_SIZE)
	{
		if (ht.buckets[i].first != NULL)
		{
			++used;
			bucket = ht.buckets[i].first;
			printf("length:%hhu\n>>>>\n", ht.buckets[i].length);
			while (bucket)
			{
				printf("name:%s\n", bucket->name);
				bucket = bucket->next;
			}
		}
		++i;
	}
	printf("buckets used: %d\n", used);
}
