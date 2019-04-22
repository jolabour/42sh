/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path_histo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 09:04:57 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/22 23:37:45 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void				init_path_histo(t_42sh *sh)
{
	struct passwd	*pw;

	pw = getpwnam(getlogin());
	if (pw)
		sh->path_history = pw->pw_dir;
	else
		sh->path_history = "/tmp";
	sh->path_history = ft_strjoin(sh->path_history, "/.42sh_history");
}
