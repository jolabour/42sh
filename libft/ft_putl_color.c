/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putl_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 00:15:03 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/27 00:15:04 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putl_blue(char *str)
{
	ft_putstr(BLUE);
	ft_putstr(str);
	ft_putendl(NORMAL);
}

void	ft_putl_red(char *str)
{
	ft_putstr(RED);
	ft_putstr(str);
	ft_putendl(NORMAL);
}

void	ft_putl_green(char *str)
{
	ft_putstr(GREEN);
	ft_putstr(str);
	ft_putendl(NORMAL);
}

void	ft_putl_yellow(char *str)
{
	ft_putstr(YELLOW);
	ft_putstr(str);
	ft_putendl(NORMAL);
}

void	ft_putl_cyan(char *str)
{
	ft_putstr(CYAN);
	ft_putstr(str);
	ft_putendl(NORMAL);
}
