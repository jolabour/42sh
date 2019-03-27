/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 07:28:33 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/27 00:23:04 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			len_list(t_env *env)
{
	int		i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char		**list_to_tab(t_env *env, char **copy_env)
{
	int		i;

	copy_env = (char**)ft_malloc_exit(sizeof(char *) * (len_list(env) + 1));
	i = 0;
	while (env)
	{
		copy_env[i] = ft_strdup(env->str);
		env = env->next;
		i++;
	}
	copy_env[i] = NULL;
	return (copy_env);
}

t_env		*create_node(char *str)
{
	t_env	*new;

	new = (t_env*)ft_malloc_exit(sizeof(*new));
	new->str = ft_strdup(str);
	new->next = NULL;
	return (new);
}

void		lst_push(t_env **head, t_env *new)
{
	t_env	*tmp;

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

t_env		*set_list(char **env)
{
	t_env	*start;
	t_env	*new;
	int		i;

	start = NULL;
	i = 0;
	while (env[i])
	{
		new = create_node(env[i]);
		lst_push(&start, new);
		i++;
	}
	return (start);
}
