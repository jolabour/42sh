/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 04:21:23 by jolabour          #+#    #+#             */
/*   Updated: 2019/01/25 01:38:08 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			main(int argc, char **argv, char **env)
{
	t_42sh	sh;

	init_shell(&sh, env);
	if (!(env[0]))
		exit(0);
	while (42)
	{
		sh.need_get_line = true;
		process(&sh);
		if (sh.lexer && argc == 2 && ft_strequ(argv[1], "--lexer"))
			print_lexer(&sh);
		if (argc == 2 && ft_strequ(argv[1], "--history"))
			print_history(sh.history_mark);
		ft_strdel(&sh.stdin->input);
		free(sh.stdin);
		del_lexer(&sh.lexer);
		del_history(sh.history_mark);
		ft_free_split(sh.argv->argv);
	}
	free(sh.argv);
	return (0);
}
