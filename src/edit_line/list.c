/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 07:28:33 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/11 20:25:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		list_del(t_env **env, t_env *to_del, t_env *prev)
{
	if (*env == to_del)
		*env = to_del->next;
	else
		prev->next = to_del->next;
	free(to_del->str);
	free(to_del);
}

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

char	**list_to_tab(t_env *env, char **copy_env)
{
	int		i;

	if (!(copy_env = malloc(sizeof(char *) * (len_list(env) + 1))))
		print_error(_ENOMEM, 1);
	i = 0;
	while (env)
	{
		if ((copy_env[i] = ft_strdup(env->str)) == NULL)
			print_error(_ENOMEM, 1);
		env = env->next;
		i++;
	}
	copy_env[i] = NULL;
	return (copy_env);
}

t_env		*create_node(char *str)
{
	t_env	*new;

	if (!(new = malloc(sizeof(*new))) || !(new->str = ft_strdup(str)))
		return (NULL);
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
		if (!(new = create_node(env[i])))
			print_error(_ENOMEM, 1);
		lst_push(&start, new);
		i++;
	}
	return (start);
}
