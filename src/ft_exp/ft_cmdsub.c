/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:26:18 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:26:38 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		ft_cmdsub_child(int pipefd[2], t_node *ast, t_42sh *shell)
{
	signal(SIGSTOP, SIG_DFL);
	close(pipefd[0]);
	if (!(shell->pgid))
		shell->pgid = shell->pid;
	if (pipefd[1] != STDOUT_FILENO)
	{
		ft_dup2_exit(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (ast)
		g_exetab[ast->token](ast, shell);
	exit(EXIT_SUCCESS);
}

void		ft_cmdsub_error(char *command)
{
	ft_putstr_fd("42sh: command substitution: `", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd("\'\n", STDERR_FILENO);
}

char		*ft_cmdsub(char *command, t_42sh *shell, bool dquote)
{
	t_ast	ast;
	int		pipefd[2];
	pid_t	pid;
	char	*result;

	ast = (t_ast){NULL, NULL, NULL};
	result = NULL;
	if (ft_cmdsub_parse(&ast, command, shell))
		ft_cmdsub_error(command);
	else
	{
		ft_pipe_exit(pipefd);
		pid = ft_fork_exit();
		if (pid == 0)
			ft_cmdsub_child(pipefd, ast.begin, shell);
		close(pipefd[1]);
		result = ft_cmdsub_read(pipefd[0], pid);
		ft_ast_free(ast.begin);
	}
	free(command);
	return (result ? ft_backslash_quotes(result, dquote) : NULL);
}
