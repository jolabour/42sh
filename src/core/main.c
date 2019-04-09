/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 04:21:23 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/09 05:25:40 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "ft_global.h"

int			main(int argc, char **argv, char **env)
{
	t_42sh	sh;

	(void)argc;
	sh.args = argv;
	init_shell(&sh, env);
	ft_init(&sh);
	if (!(env[0]))
		exit(0);
	while (42)
	{
		sh.need_get_line = true;
		process(&sh);
		ft_strdel(&sh.stdin->input);
		free(sh.stdin);
		del_history(sh.history_mark);
		//sh.argv->argv = ft_free_split(sh.argv->argv);
	}
	free(sh.argv);
	return (0);
}
