/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 09:47:17 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 09:58:44 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_btn			ft_isbuiltin(char *word)
{
	int			i;

	i = 0;
	while (g_bttab[i].name && !ft_strequ(g_bttab[i].name, word))
		i++;
	return (g_bttab[i].f);
}

int				ft_count_argvsize(char **args)
{
	int			i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int				ft_exe_builtin(t_node *current, t_42sh *shell,
				void (*f)(t_42sh *))
{
	t_tmpfd		*tmp;
	int			ret;

	ret = 0;
	if (current->redir)
		ret = g_exetab[current->redir->token](current->redir, shell);
	tmp = shell->tmp_fds;
	shell->tmp_fds = NULL;
	shell->argv->size = ft_count_argvsize(shell->argv->argv);
	if (!ret)
		f(shell);
	ft_reset_tmp_fd(tmp);
	return (ret ? ret : shell->retval);
}
