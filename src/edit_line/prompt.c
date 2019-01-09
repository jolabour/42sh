/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 08:56:10 by jolabour          #+#    #+#             */
/*   Updated: 2018/08/17 04:09:21 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		prompt(t_env *list, t_42sh *sh)
{
	char	buf[270];
	char	*pwd;
	char	*home;
	size_t	len_home;

	ft_strcpy(buf, "\x1B[1;33m| \x1B[1;36m");
	if ((pwd = ft_getenv(list, "PWD=", 4)) != NULL)
	{
		if ((home = ft_getenv(list, "HOME=", 5)) != NULL)
		{
			len_home = ft_strlen(home);
			if (home[len_home - 1] == '/')
				--len_home;
		}
		if (home && ft_strncmp(pwd, home, len_home) == 0)
		{
			pwd += len_home;
			ft_strcat(buf, "~");
			if (pwd[0] == '/' && pwd[1] != '\0')
				ft_strcat(buf, pwd);
		}
		else
			ft_strcat(buf, pwd);
	}
	ft_strcat(buf, "\x1B[1;33m | \x1B[1;32m$> \x1B[0;0m");
	ft_putstr(buf);
	sh->prompt_len = ft_strlen(buf) - 34;
}
