/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tmp_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 02:06:29 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/20 02:06:32 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			add_tmp_env(t_42sh *sh, char *str, char *to_export)
{
	char		*join;
	t_env		*new;

	join = ft_strjoin(str, to_export);
	new = create_node(join);
	lst_push(&sh->env, new);
	free(join);
}

int				check_tmp_env(t_42sh *sh, char *str)
{
	char		*name;
	char		*to_export;
	char		**split;

	name = ft_strjoin(str, "=");
	if ((to_export = getenv_cd(sh->copy_env, name, ft_strlen(name), NULL))
			== NULL)
	{
		free(name);
		return (0);
	}
	split = ft_malloc_exit(sizeof(char*) * 3);
	split[0] = ft_strdup(str);
	split[1] = ft_strdup(to_export);
	split[2] = NULL;
	if (check_env(&sh->env, split) == 0)
		add_tmp_env(sh, name, to_export);
	ft_free_split(split);
	free(name);
	return (1);
}
