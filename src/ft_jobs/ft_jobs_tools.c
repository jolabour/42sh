/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:31:34 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 11:32:42 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_joblist		*ft_search_job(t_joblist *list, int num)
{
	while (list)
	{
		if (list->num == num)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void			ft_print_bg(t_joblist *job, t_42sh *shell)
{
	ft_putstr_fd("[", STDERR_FILENO);
	ft_putnbr_fd(job->num, STDERR_FILENO);
	ft_putstr_fd("] ", STDERR_FILENO);
	ft_putnbr_fd(shell->last_bg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
