/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 04:21:23 by jolabour          #+#    #+#             */
/*   Updated: 2018/07/29 07:42:21 by jolabour         ###   ########.fr       */
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
		//free_all(&sh);
	}
	return (0);
}
