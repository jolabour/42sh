/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 05:07:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/08/17 04:24:05 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** Hash table implementation that handles collision
*/

unsigned int 	hash(const char *s)
{
	unsigned int 	hashval;

	hashval = 0;
	while (*s != '\0')
	{
		hashval = *s + (31 * hashval);
		++s;
	}
	return (hashval % HASHTABLESIZE);
}

HASHTABLE 		*ht_lookup(const char *s, HASHTABLE *ht[HASHTABLESIZE])
{
	HASHTABLE 	*entry;

	entry = ht[hash(s)];
	while (entry != NULL)
	{
		if (ft_strcmp(s, entry->name) == 0)
			return (entry);
		entry = entry->next;
	}
	return (NULL);
}

HASHTABLE 		*ht_insert(const char *name, HASHTABLE *ht[HASHTABLESIZE])
{
	HASHTABLE 		*entry;
	unsigned int 	hashval;

	if ((entry = ht_lookup(name, ht)) == NULL)
	{
		entry = (HASHTABLE*)malloc(sizeof(*entry));
		if (entry == NULL || (entry->name = ft_strdup(name)) == NULL)
			return (NULL);
		hashval = hash(name);
		entry->next = ht[hashval];
		ht[hashval] = entry;
	}
	return (entry);
}

void 			ht_delete(const char *name, HASHTABLE *ht[HASHTABLESIZE])
{
	HASHTABLE 	*entry;
	HASHTABLE 	*tmp;

	entry = ht[hash(name)];
	if (ft_strcmp(name, entry->name) == 0)
	{
		tmp = entry;
		free(entry->name);
		free(tmp);
	}
	else
	{
		while (entry->next != NULL)
		{
			if (ft_strcmp(name, entry->next->name) == 0)
			{
				free(entry->next->name);
				free(entry->next);
				entry->next = NULL;
			}
			entry = entry->next;
		}
	}
}
