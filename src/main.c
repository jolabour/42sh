/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 04:21:23 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/06 01:00:28 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			main(int argc, char **argv, char **env)
{
	t_42sh	sh;

	argc = 1;
	argv = NULL;
	init_shell(&sh, env);
	if (!(env[0]))
		exit(0);
	while (42)
	{
		process(&sh);
		ft_strdel(&sh.stdin->input);
		free(sh.stdin);
		print_lexer(&sh);
		del_lexer(&sh);
		free(sh.lexer);
		//free(sh.lexer);
		//free_all(&sh);
	}
	return (0);
}
