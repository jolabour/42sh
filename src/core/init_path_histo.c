/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path_histo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 09:04:57 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/12 09:17:00 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		init_path_histo(t_42sh *sh)
{
	char	*name;
	char	*tmp;

	name = getlogin();
	tmp = ft_strjoin("/Users/", name);
	sh->path_history = ft_strjoin(tmp, "/.42sh_history");
	ft_putendl(sh->path_history);
	free(tmp);
	free(name);
}
