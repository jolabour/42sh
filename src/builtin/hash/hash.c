#include "sh.h"

void		reset_hashtable(t_ht *ht)
{
	BUCKET_CONTENT		*tmp;
	unsigned int		i;
	uint8_t	j;

	i = 0;
	while (i < INITIAL_HASHTABLE_SIZE)
	{
		if (ht->buckets[i].first != NULL)
		{
			j = ht->buckets[i].length;
			while (j > 0)
			{
				tmp = ht->buckets[i].first;
				ht->buckets[i].first = ht->buckets[i].first->next;
				ft_strdel(&tmp->name);
				ft_strdel(&tmp->path);
				tmp->pathlen = 0;
				free(tmp);
				tmp = NULL;
				j--;
			}
			ht->buckets[i].length = 0;
			ht->buckets[i].first = NULL;
		}
		i++;
	}
}

void		check_hash_opt(t_42sh *sh)
{
	int		i;
	char	*path;

	i = 1;
	if (sh->argv->argv[i][0] == '-')
	{
		if (ft_strequ(sh->argv->argv[i], "-r") == 1)
		{
			reset_hashtable(&sh->hashtable);
			i++;
		}
		else if (ft_strequ(sh->argv->argv[i], "-a") == 1)
		{
			init_hashtable(sh);
			i++;
		}
		else
		{
			ft_putstr_fd("42sh: hash: ", 2);
			ft_putstr_fd(sh->argv->argv[1], 2);
			ft_putstr_fd(": invalid option\n", 2);
			ft_putstr_fd("hash: usage: hash [-r] [-a] [name ...]\n", 2);
			return ;
		}
	}
	while (sh->argv->argv[i])
	{
		if (sh->argv->argv[i][0] == '/' || check_is_builtin(sh, sh->argv->argv[i]) == 1);
		else if (ht_lookup(sh->argv->argv[i], &sh->hashtable) == NULL)
		{
			if ((path = check_access(sh, i)) != NULL)
				ht_insert(path, sh->argv->argv[i], &sh->hashtable);
			else
			{
				ft_putstr_fd("42sh: hash: ", 2);
				ft_putstr_fd(sh->argv->argv[i], 2);
				ft_putstr_fd(": not found\n", 2);
			}
			ft_strdel(&path);
		}
		i++;
	}
}

void		builtin_hash(t_42sh *sh)
{
	if (sh->argv->size == 1)
		print_hashtable(sh->hashtable);
	else
		check_hash_opt(sh);
}
