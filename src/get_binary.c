/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 04:30:08 by jolabour          #+#    #+#             */
/*   Updated: 2018/09/06 01:42:10 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <dirent.h>

void		hash_current_dir(t_ht *ht, DIR *dirp, char *path)
{
	struct dirent	*de;
	char			*real_path;

	while ((de = readdir(dirp)) != NULL)
	{
		real_path = ft_strjoin(path, de->d_name);
		if (de->d_type == DT_REG
				&& access(real_path, X_OK)
				&& (ft_strcmp(de->d_name, ".") != 0)
				&& (ft_strcmp(de->d_name, "..") != 0))
			ht_insert(de->d_name, ht);
		free(real_path);
	}
}

void		open_dir(char *path, t_ht *ht)
{
	DIR		*dirp;

	if (!(dirp = opendir(path)))
		return ;
	hash_current_dir(ht, dirp, path);
	if (closedir(dirp) == -1)
		return ;
}

void		get_binary(t_42sh *sh)
{
	int		i;

	i = 0;
	while (sh->bin_dirs[i] != 0)
	{
		open_dir(sh->bin_dirs[i], &sh->hashtable);
		i++;
	}
}

void		print_hashtable(t_ht ht)
{
	int				i;
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
