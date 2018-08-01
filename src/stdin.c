/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 09:09:06 by jolabour          #+#    #+#             */
/*   Updated: 2018/08/01 21:55:28 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <stdio.h>

void		get_line(t_42sh *sh)
{
	int		i;
	char	buf[4];
	char	*tmp;
	//ft_bzero(sh->input, 256);
	sh->line_pos = 0;
	sh->len_line = 0;
	while (42)
	{
		if ((i = read(0, buf, 3)) > 0)
		{
			buf[i] = '\0';
			if (buf[0] == 27 && buf[2] == 'A')
				;
			else if (buf[0] == 27 && buf[2] == 'B')
				;
			else if (buf[0] == 27 && buf[2] == 'C')
				move_to_right(sh);
			else if (buf[0] == 27 && buf[2] == 'D')
				move_to_left(sh);
			else if (buf[0] == 4)
				exit(EXIT_SUCCESS);
			else if (buf[0] == '\n')
			{
				sh->input[sh->line_pos] = '\0';
				ft_putchar('\n');
				return ;
			}
			else
			{
				ft_putstr_fd(buf, 0);
				if (sh->line_pos != sh->len_line)
				{
					tmp = ft_strdup(sh->input + sh->line_pos);
					sh->input[sh->line_pos] = buf[0];
					ft_strcpy(sh->input + sh->line_pos + 2, tmp);
					free(tmp);
					//ft_putendl(sh->input);
				}
				else
				{
					sh->input[sh->line_pos] = buf[0];
					sh->input[sh->line_pos + 1] = '\0';
				}
				sh->line_pos++;
				sh->len_line++;
			}
		}
	}
}
