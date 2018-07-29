/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 19:18:22 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/01/12 10:25:43 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifdef BUFF_SIZE
#  undef BUFF_SIZE
# endif
# define BUFF_SIZE 512

# define DELIM '\n'

typedef struct s_hist	t_hist;

typedef struct s_file	t_file;

struct		s_file
{
	char	*saved;
	size_t	saved_len;
	int		fd;
	t_file	*next;
};

struct		s_hist
{
	t_file	*files;
};

int			get_next_line(const int fd, char **line);

#endif
