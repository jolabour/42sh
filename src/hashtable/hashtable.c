/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 05:07:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/09/06 07:23:18 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef DEBUG

# include <stdio.h>
# include <assert.h>
# include <stdlib.h>

#endif

#include "sh.h"

/*
** Bash's string hash function
*/

unsigned int		hash_str(const char *s)
{
	register unsigned int 	hash;

	hash = 0;
	while (*s != '\0')
	{
		hash *= 16777619;
		hash ^= *s;
		++s;
	}
	return (hash);
}

BUCKET_CONTENT		*ht_lookup(const char *s, t_ht *ht)
{
	BUCKET_CONTENT	*entry;
	uint16_t		index;

	index = (hash_str(s) & (INITIAL_HASHTABLE_SIZE - 1));
	entry = ht->buckets[index].first;
	while (entry != NULL)
	{
		if (ft_strcmp(s, entry->name) == 0)
			break ;
		entry = entry->next;
	}
	return (entry);
}

BUCKET_CONTENT 		*ht_insert(const char *path, const char *name, t_ht *ht)
{
	BUCKET_CONTENT 	*entry;
	unsigned int 	index;

	if ((entry = ht_lookup(name, ht)) == NULL)
	{
		entry = (BUCKET_CONTENT*)malloc(sizeof(*entry));
		if (entry == NULL
				|| (entry->name = ft_strdup(name)) == NULL
				|| (entry->path = ft_strdup(path)) == NULL)
			return (NULL);
		index = hash_str(name) & (INITIAL_HASHTABLE_SIZE - 1);
		entry->next = ht->buckets[index].first;
		ht->buckets[index].first = entry;
		ht->buckets[index].length++;
	}
	return (entry);
}

void				ht_delete(const char *name, t_ht *ht)
{
	BUCKET_CONTENT 	*entry;
	BUCKET_CONTENT	*tmp;
	uint16_t		index;

	index = hash_str(name) & (ht->capacity - 1);
	entry = ht->buckets[index].first;
	if (ft_strcmp(name, entry->name) == 0)
	{
		ht->buckets[index].first = entry->next;
		free(entry->name);
		free(entry->path);
		free(entry);
	}
	else
	{
		while (entry->next != NULL)
		{
			if (ft_strcmp(name, entry->next->name) == 0)
			{
				tmp = entry->next;
				entry->next = entry->next->next;
				free(tmp->name);
				free(tmp->path);
				free(tmp);
			}
			entry = entry->next;
		}
	}
}
