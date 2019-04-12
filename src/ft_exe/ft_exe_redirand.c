/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_redirand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 09:25:46 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 09:29:56 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_exe_lessand(t_node *current, t_42sh *shell)
{
	char		*fd;
	int			dest;
	int			src;
	int			ret;

	dest = current->left ? ft_atoi(current->left->data) : 0;
	if (!(fd = ft_simple_expanse(current->right->data, shell)))
		return (1);
	if (!ft_str_isdigit(fd) || !fd[0])
		return (ft_ambigous_error(fd, current->right->data));
	src = ft_atoi(fd);
	ret = fcntl(src, F_GETFD);
	if (ft_strlen(fd) > 10 || (ft_strlen(fd) == 10
		&& ft_strcmp(fd, "2147483647") > 0) || ret == -1 || ret & FD_CLOEXEC)
		return (ft_badfd_error(fd, current->right->data));
	free(fd);
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	if (dest != src)
		ft_dup2_exit(src, dest);
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}

int				ft_exe_lessanddash(t_node *current, t_42sh *shell)
{
	int			dest;

	dest = current->left ? ft_atoi(current->left->data) : 0;
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	close(dest);
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}

int				ft_exe_greatand(t_node *current, t_42sh *shell)
{
	char		*fd;
	int			dest;
	int			src;
	int			ret;

	dest = current->left ? ft_atoi(current->left->data) : 1;
	if (!(fd = ft_simple_expanse(current->right->data, shell)))
		return (1);
	if (!ft_str_isdigit(fd) || !fd[0])
		return (ft_ambigous_error(fd, current->right->data));
	src = ft_atoi(fd);
	ret = fcntl(src, F_GETFD);
	if (ft_strlen(fd) > 10 || (ft_strlen(fd) == 10
		&& ft_strcmp(fd, "2147483647") > 0) || ret == -1 || ret & FD_CLOEXEC)
		return (ft_badfd_error(fd, current->right->data));
	free(fd);
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	if (dest != src)
		ft_dup2_exit(src, dest);
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}

int				ft_exe_greatanddash(t_node *current, t_42sh *shell)
{
	int			dest;

	dest = current->left ? ft_atoi(current->left->data) : 1;
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	close(dest);
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}
