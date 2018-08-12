/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 02:43:02 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/29 07:47:13 by jolabour         ###   ########.fr       */
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
	g_errors[_ENOCMD - 1] = "minishell: command not found: ";
	g_errors[_ENOX - 1] = "minishell: permission denied: ";
}

void	print_error_and_exit(int error_code)
{
	ft_putendl_fd(g_errors[error_code - 1], 2);
	exit(EXIT_FAILURE);
}

void	print_error(int error_code)
{
	ft_putendl_fd(g_errors[error_code - 1], 2);
	g_errno = 0;
}

void	print_error_first(int error_code)
{
	ft_putstr_fd(g_errors[error_code - 1], 2);
}
