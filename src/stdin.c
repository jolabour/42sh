/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 09:09:06 by jolabour          #+#    #+#             */
/*   Updated: 2018/07/29 10:48:09 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		get_line(char *line)
{
	char buf[3];

	line = NULL;
	while (read(0, buf, 3) == 1)
	{
		if (buf[0] == 27)
		{
			ft_putendl("c'est insane");
			return ;
		}
		//else if (buf[0] == KEY_RIGHT)
			//line = go_to_right(line);
		else if (buf[0] == '\n')
			return ;
		else
			ft_strcat(line, buf);
	}
}
