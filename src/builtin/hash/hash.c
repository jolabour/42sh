/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 04:10:56 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/20 01:51:29 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		reset_hashtable(t_ht *ht)
{
	BUCKET_CONTENT		*tmp;
	unsigned int		i;
	uint8_t				j;

	i = 0;
	while (i < INITIAL_HASHTABLE_SIZE)
	{
		if (ht->buckets[i].first != NULL)
		{
			j = ht->buckets[i].length + 1;
			while (--j > 0)
			{
				tmp = ht->buckets[i].first;
				ht->buckets[i].first = ht->buckets[i].first->next;
				ft_strdel(&tmp->name);
				ft_strdel(&tmp->path);
				tmp->pathlen = 0;
				free(tmp);
				tmp = NULL;
			}
			ht->buckets[i].length = 0;
			ht->buckets[i].first = NULL;
		}
		i++;
	}
}

int			check_hash_opt(t_42sh *sh, char *str, int *i)
{
	if (ft_strequ(str, "-r") == 1)
	{
		reset_hashtable(&sh->hashtable);
		*i = *i + 1;
	}
	else if (ft_strequ(str, "-a") == 1)
	{
		reset_hashtable(&sh->hashtable);
		init_hashtable(sh);
		*i = *i + 1;
	}
	else
	{
		ft_putstr_fd("42sh: hash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("hash: usage: hash [-r] [-a] [name ...]\n", 2);
		sh->retval = 1;
		return (0);
	}
	return (1);
}

int			check_slash(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void		check_hash(t_42sh *sh)
{
	int		i;
	char	*path;

	i = 0;
	if (sh->argv->argv[i + 1][0] == '-')
		if (check_hash_opt(sh, sh->argv->argv[i + 1], &i) == 0)
			return ;
	while (sh->argv->argv[++i])
		if (check_slash(sh->argv->argv[i]) == 1 ||
			check_is_builtin(sh->argv->argv[i]) == 1)
			continue ;
		else if (ht_lookup(sh->argv->argv[i], &sh->hashtable) == NULL)
		{
			if ((path = check_access(sh, i)) != NULL)
				ht_insert(path, sh->argv->argv[i], &sh->hashtable);
			else
			{
				ft_putstr_fd("42sh: hash: ", 2);
				ft_putstr_fd(sh->argv->argv[i], 2);
				ft_putstr_fd(": not found\n", 2);
				sh->retval = 1;
			}
			ft_strdel(&path);
		}
}

void		builtin_hash(t_42sh *sh)
{
	sh->retval = 0;
	if (sh->argv->size == 1)
		print_hashtable(sh->hashtable);
	else
		check_hash(sh);
	if (sh->retval == 1)
		return ;
	sh->retval = 0;
}
