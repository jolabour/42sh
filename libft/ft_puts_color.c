/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 00:15:16 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/27 00:15:17 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puts_blue(char *str)
{
	ft_putstr(BLUE);
	ft_putstr(str);
	ft_putstr(NORMAL);
}

void	ft_puts_red(char *str)
{
	ft_putstr(RED);
	ft_putstr(str);
	ft_putstr(NORMAL);
}

void	ft_puts_green(char *str)
{
	ft_putstr(GREEN);
	ft_putstr(str);
	ft_putstr(NORMAL);
}

void	ft_puts_yellow(char *str)
{
	ft_putstr(YELLOW);
	ft_putstr(str);
	ft_putstr(NORMAL);
}

void	ft_puts_cyan(char *str)
{
	ft_putstr(CYAN);
	ft_putstr(str);
	ft_putstr(NORMAL);
}
