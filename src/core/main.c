/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 04:21:23 by jolabour          #+#    #+#             */
/*   Updated: 2019/01/22 02:02:18 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			main(int argc, char **argv, char **env)
{
	t_42sh	sh;
	int		i;

	init_shell(&sh, env);
	if (!(env[0]))
		exit(0);
	while (42)
	{
		process(&sh);
		if (sh.lexer && argc == 2 && ft_strequ(argv[1], "--lexer"))
			print_lexer(&sh);
		if (argc == 2 && ft_strequ(argv[1], "--history"))
			print_history(sh.history_mark);
		ft_strdel(&sh.stdin->input);
		free(sh.stdin);
		del_lexer(&sh.lexer);
		del_history(sh.history_mark);
		i = 0;
		while (sh.argv->argv[i])
		{
			ft_strdel(&sh.argv->argv[i]);
			i++;
		}
		ft_strdel(&sh.argv->argv[i]);
		ft_strdel(sh.argv->argv);
		//free(sh.lexer);
		//free(sh.lexer);
		//free_all(&sh);
	}
	free(sh.argv);
	return (0);
}
