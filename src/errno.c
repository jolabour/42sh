/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 02:43:02 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/09/08 01:55:51 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_set_errno(int n)
{
	g_errno = n;
	return (-1);
}
 void	init_error_tab(void)
{
	g_errors[_ENOMEM - 1] = "Cannot allocate memory";
	g_errors[_ENOENV - 1] = "Env is missing";
	g_errors[_ENAMEENV - 1] = "Setenv: Variable name must contain alphanumeric "
		"characters and must begin with a letter.";
	g_errors[_ENOHOME - 1] = "~ : HOME unset.";
	g_errors[_ENOUSER - 1] = "Unknown user: ";
	g_errors[_ENOVAR - 1] = ": Undefined variable.";
	g_errors[_ENOCMD - 1] = PROG_NAME ": command not found: ";
	g_errors[_ENOX - 1] = PROG_NAME ": permission denied: ";
}

inline void	print_error(int code, bool is_fatal)
{
	ft_putendl_fd(g_errors[code - 1], 2);
	if (is_fatal)
		exit(EXIT_FAILURE);
}
