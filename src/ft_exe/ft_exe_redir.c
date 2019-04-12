/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 09:19:25 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 09:30:56 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_exe_great(t_node *current, t_42sh *shell)
{
	char		*path;
	int			dest;
	int			src;

	dest = current->left ? ft_atoi(current->left->data) : 1;
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	if (!(path = ft_simple_expanse(current->right->data, shell)))
		return (1);
	if ((src = open(path, O_WRONLY)) == -1)
	{
		if ((src = ft_open_error(path, O_WRONLY | O_CREAT,
			current->right->data)) == -1)
			return (1);
		fchmod(src, 0644);
	}
	free(path);
	if (dest != src)
	{
		ft_dup2_exit(src, dest);
		close(src);
	}
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}

int				ft_exe_less(t_node *current, t_42sh *shell)
{
	char		*path;
	int			dest;
	int			src;

	dest = current->left ? ft_atoi(current->left->data) : 0;
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	if (!(path = ft_simple_expanse(current->right->data, shell)))
		return (1);
	if ((src = ft_open_error(path, O_RDONLY, current->right->data)) == -1)
		return (1);
	free(path);
	if (dest != src)
	{
		ft_dup2_exit(src, dest);
		close(src);
	}
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}

int				ft_exe_dless(t_node *current, t_42sh *shell)
{
	int			dest;
	int			pipefd[2];
	char		*heredoc;

	dest = current->left ? ft_atoi(current->left->data) : 0;
	ft_pipe_exit(pipefd);
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	if (!(heredoc = ft_str_isquote(current->right->data)
		? ft_strdup(current->right->right->data)
		: ft_simple_expanse(current->right->right->data, shell)))
		return (1);
	ft_putstr_fd(heredoc, pipefd[1]);
	free(heredoc);
	close(pipefd[1]);
	if (dest != pipefd[0])
	{
		ft_dup2_exit(pipefd[0], dest);
		close(pipefd[0]);
	}
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}

int				ft_exe_dgreat(t_node *current, t_42sh *shell)
{
	char		*path;
	int			dest;
	int			src;

	dest = current->left ? ft_atoi(current->left->data) : 1;
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	if (!(path = ft_simple_expanse(current->right->data, shell)))
		return (1);
	if ((src = open(path, O_WRONLY | O_APPEND)) == -1)
	{
		if ((src = ft_open_error(path, O_WRONLY | O_APPEND | O_CREAT,
			current->right->data)) == -1)
			return (1);
		fchmod(src, 0644);
	}
	free(path);
	if (dest != src)
	{
		ft_dup2_exit(src, dest);
		close(src);
	}
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}

int				ft_exe_lessgreat(t_node *current, t_42sh *shell)
{
	char		*path;
	int			dest;
	int			src;

	if (!(path = ft_simple_expanse(current->right->data, shell)))
		return (1);
	dest = current->left ? ft_atoi(current->left->data) : 0;
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	if ((src = open(path, O_RDWR)) == -1)
	{
		if ((src = ft_open_error(path, O_RDWR
			| O_CREAT, current->right->data)) == -1)
			return (1);
		fchmod(src, 0644);
	}
	free(path);
	if (dest != src)
	{
		ft_dup2_exit(src, dest);
		close(src);
	}
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}
