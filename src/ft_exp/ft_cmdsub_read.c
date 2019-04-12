/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdsub_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:24:56 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:25:37 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*ft_del_ending_newlines(char *str)
{
	size_t	i;
	size_t	last;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			last = i;
			while (str[i] == '\n')
				i++;
			if (!str[i])
				str[last] = '\0';
		}
		else
			i++;
	}
	return (str);
}

char		*ft_cmdsub_read(int fd, pid_t pid)
{
	char	*sub;
	char	buf[BUFF_SIZE + 1];
	int		ret;

	sub = ft_strdup("");
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		sub = ft_strjoinfree(sub, buf, 1);
	}
	if (waitpid(pid, &ret, 0) && WIFSIGNALED(ret) && WTERMSIG(ret) == SIGINT)
	{
		free(sub);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (NULL);
	}
	ft_del_ending_newlines(sub);
	close(fd);
	return (sub);
}
