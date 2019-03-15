/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:15:15 by geargenc          #+#    #+#             */
/*   Updated: 2019/03/15 01:46:48 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

#define VOID (void)argc;(void)argv;(void)envp

int				ft_exe_badtoken(t_node *current, t_shell *shell)
{
	(void)current;
	(void)shell;
	return (-1);
}

t_proclist		*ft_get_pipeline(t_node *current)
{
	t_proclist	*process;

	if (!(process = (t_proclist *)malloc(sizeof(t_proclist))))
		return (NULL);
	*process = (t_proclist){0, NULL, 0, NULL, NULL, NULL};
	if (current->token == PIPE)
	{
		process->command = current->left;
		if (!(process->next = ft_get_pipeline(current->right)))
			return (NULL);
	}
	else
	{
		process->command = current;
		process->next = NULL;
	}
	return (process);
}

int				ft_get_job_number(t_joblist *jobs)
{
	int			max;

	max = 0;
	while (jobs)
	{
		if (jobs->num > max)
			max = jobs->num;
		jobs = jobs->next;
	}
	return (max + 1);
}

t_joblist		*ft_get_job(t_node *current, t_shell *shell)
{
	t_joblist	*job;

	if (!(job = (t_joblist *)malloc(sizeof(t_joblist)))
		|| !(job->process = ft_get_pipeline(current)))
		return (NULL);
	if (shell->pgid)
		job->pgid = shell->pgid;
	else
		job->pgid = 0;
	job->command = current;
	job->next = NULL;
	job->num = ft_get_job_number(shell->jobs);
	return (job);
}

void			ft_reset_signals(void)
{
	signal (SIGINT, SIG_DFL);
    signal (SIGQUIT, SIG_DFL);
    signal (SIGTSTP, SIG_DFL);
    signal (SIGTTIN, SIG_DFL);
    signal (SIGTTOU, SIG_DFL);
}

void			ft_launch_process(t_proclist *proc, t_shell *shell,
				int pipefd[3], pid_t pgid)
{
	setpgid(getpid(), (pgid = pgid ? pgid : getpid()));
	if (!shell->pgid && shell->foreground)
		tcsetpgrp(STDIN_FILENO, pgid);
	if (!shell->pgid)
		ft_reset_signals();
	shell->pgid = pgid;
	if (pipefd[2] != -1 && dup2(pipefd[2], 0) == -1)
		exit(1);
	close(pipefd[2]);
	if (pipefd[1] != -1 && dup2(pipefd[1], 1) == -1)
		exit(1);
	close(pipefd[1]);
	close(pipefd[0]);
	shell->forked = 1;
	if (proc->path)
	{
		if (proc->command->redir && g_exetab[proc->command->redir->token]
			(proc->command->redir, shell))
			exit(1);
		execve(proc->path, proc->args, NULL);
		exit(1);
	}
	exit(g_exetab[proc->command->token](proc->command, shell));
}

void			ft_launch_job(t_joblist *job, t_shell *shell)
{
	t_proclist	*proc;
	int			pipefd[3];

	proc = job->process;
	pipefd[2] = -1;
	while (proc)
	{
		if (proc->next && pipe(pipefd) == -1)
			exit(2);
		if (!proc->next)
			pipefd[1] = -1;
		if ((proc->pid = fork()) < 0)
			exit(2);
		if (!proc->pid)
			ft_launch_process(proc, shell, pipefd, job->pgid);
		if (job->pgid == 0)
			job->pgid = proc->pid;
		setpgid(proc->pid, job->pgid);
		close(pipefd[1]);
		close(pipefd[2]);
		pipefd[2] = pipefd[0];
		proc = proc->next;
	}
}

void			ft_write_status(int status)
{
	ft_putstr("WIFEXITED: ");
	ft_putnbr(WIFEXITED(status));
	ft_putstr(" - WEXITSTATUS: ");
	ft_putnbr(WEXITSTATUS(status));
	ft_putstr("\nWIFSIGNALED: ");
	ft_putnbr(WIFSIGNALED(status));
	ft_putstr(" - WTERMSIG: ");
	ft_putnbr(WTERMSIG(status));
	ft_putstr("\nWIFSTOPPED: ");
	ft_putnbr(WIFSTOPPED(status));
	ft_putstr(" - WSTOPSIG: ");
	ft_putnbr(WSTOPSIG(status));
	ft_putstr("\nWCOREDUMP: ");
	ft_putnbr(WCOREDUMP(status));
	ft_putstr("\nisatty: ");
	ft_putnbr(isatty(1));
	ft_putstr("\n");
}

int				ft_wait_job(t_joblist *job)
{
	t_proclist	*proc;

	proc = job->process;
	while (proc && proc->next)
	{
		waitpid(proc->pid, &(proc->status), WUNTRACED);
		proc = proc->next;
	}
	waitpid(proc->pid, &(proc->status), WUNTRACED);
	ft_write_status(proc->status);
	return (proc->status);
}

int				ft_exe_pipe(t_node *current, t_shell *shell)
{
	t_joblist	*job;
	int			status;

	shell->forked = 0;
	if (!(job = ft_get_job(current, shell)))
		exit(2);
	ft_launch_job(job, shell);
	if (!shell->pgid && shell->foreground)
		tcsetpgrp(STDIN_FILENO, job->pgid);
	status = ft_wait_job(job);
	if (!shell->pgid && shell->foreground)
		tcsetpgrp(STDIN_FILENO, shell->pid);
	return (WEXITSTATUS(status));
}

int				ft_exe_and(t_node *current, t_shell *shell)
{
	t_joblist	*job;
	int			foreground;

	shell->forked = 0;
	if (!(job = ft_get_job(current->left, shell)))
		exit(2);
	foreground = shell->foreground;
	shell->foreground = 0;
	ft_launch_job(job, shell);
	shell->foreground = foreground;
	shell->retval = 0;
	if (current->right)
		shell->retval = g_exetab[current->right->token](current->right, shell);
	return (shell->retval);
}

int				ft_exe_semi(t_node *current, t_shell *shell)
{
	int			ret;

	if (current->right)
		shell->forked = 0;
	if ((ret = g_exetab[current->left->token](current->left, shell)) < 0)
		return (ret);
	if (current->right)
		ret = g_exetab[current->right->token](current->right, shell);
	return (ret);
}

int				ft_dup_tmp_fd(int fd)
{
	int			cpy;
	int			denied[3];

	denied[0] = 0;
	denied[1] = 0;
	denied[2] = 0;
	while ((cpy = dup(fd)) >= 0 && cpy <= 2)
		denied[cpy] = 1;
	if (denied[0])
		close(0);
	if (denied[1])
		close(1);
	if (denied[2])
		close(2);
	return (cpy);
}

void			ft_build_tmp_fd(int fd, t_tmpfd **begin)
{
	t_tmpfd		*tmp;
	int			cloexec;

	if ((cloexec = fcntl(fd, F_GETFD)) != -1)
	{
		if (!(tmp = (t_tmpfd *)malloc(sizeof(t_tmpfd))))
			exit(2);
		tmp->initial = fd;
		if ((tmp->tmp = ft_dup_tmp_fd(fd)) == -1)
			exit(2);
		tmp->cloexec = cloexec;
		fcntl(tmp->tmp, F_SETFD, FD_CLOEXEC);
		tmp->next = *begin;
		*begin = tmp;
	}
}

void			ft_reset_tmp_fd(t_tmpfd *begin)
{
	t_tmpfd		*tmp;

	while (begin)
	{
		if (dup2(begin->tmp, begin->initial) == -1)
			exit(2);
		close(begin->tmp);
		fcntl(begin->initial, F_SETFD, begin->cloexec);
		tmp = begin;
		begin = begin->next;
		free(tmp);
	}
}

int				ft_exe_great(t_node *current, t_shell *shell)
{
	int			dest;
	int			src;

	dest = current->left ? ft_atoi(current->left->data) : 1;
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	if ((src = open(current->right->data, O_WRONLY)) == -1)
	{
		if ((src = open(current->right->data, O_WRONLY | O_CREAT)) == -1)
			return (1);
		fchmod(src, 0644);
	}
	if (dest != src)
	{
		if (dup2(src, dest) == -1)
			exit(2);
		close(src);
	}
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}

int				ft_exe_less(t_node *current, t_shell *shell)
{
	int			dest;
	int			src;

	dest = current->left ? ft_atoi(current->left->data) : 0;
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	if ((src = open(current->right->data, O_RDONLY)) == -1)
		return (1);
	if (dest != src)
	{
		if (dup2(src, dest) == -1)
			exit(2);
		close(src);
	}
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}

int				ft_exe_rpar(t_node *current, t_shell *shell)
{
	t_joblist	*job;
	int			status;

	if (!shell->forked)
	{
		if (!(job = ft_get_job(current, shell)))
			exit(2);
		ft_launch_job(job, shell);
		if (!shell->pgid && shell->foreground)
			tcsetpgrp(STDIN_FILENO, job->pgid);
		status = ft_wait_job(job);
		if (!shell->pgid && shell->foreground)
			tcsetpgrp(STDIN_FILENO, shell->pid);
		return (WEXITSTATUS(status));
	}
	if (current->redir
		&& g_exetab[current->redir->token](current->redir, shell))
		exit(1);
	exit(g_exetab[current->right->token](current->right, shell));
}

int				ft_exe_and_if(t_node *current, t_shell *shell)
{
	int			ret;

	shell->forked = 0;
	if ((ret = g_exetab[current->left->token](current->left, shell)))
		return (ret);
	return (g_exetab[current->right->token](current->right, shell));
}

int				ft_exe_or_if(t_node *current, t_shell *shell)
{
	int			ret;

	shell->forked = 0;
	if ((ret = g_exetab[current->left->token](current->left, shell)) < 1)
		return (ret);
	return (g_exetab[current->right->token](current->right, shell));
}

int				ft_exe_dgreat(t_node *current, t_shell *shell)
{
	int			dest;
	int			src;

	dest = current->left ? ft_atoi(current->left->data) : 1;
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	if ((src = open(current->right->data, O_WRONLY | O_APPEND)) == -1)
	{
		if ((src = open(current->right->data,
			O_WRONLY | O_APPEND | O_CREAT)) == -1)
			return (1);
		fchmod(src, 0644);
	}
	if (dest != src)
	{
		if (dup2(src, dest) == -1)
			exit(2);
		close(src);
	}
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}

int				ft_str_isdigit(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int				ft_exe_lessand(t_node *current, t_shell *shell)
{
	int			dest;
	int			src;

	dest = current->left ? ft_atoi(current->left->data) : 0;
	if (!ft_str_isdigit(current->right->data))
		return (1);
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	src = ft_atoi(current->right->data);
	if (dest != src && dup2(src, dest) == -1)
		exit(2);
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}

int				ft_exe_lessanddash(t_node *current, t_shell *shell)
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

int				ft_exe_greatand(t_node *current, t_shell *shell)
{
	int			dest;
	int			src;

	if (!(ft_str_isdigit(current->right->data)))
		return (ft_exe_and(current, shell));
	dest = current->left ? ft_atoi(current->left->data) : 1;
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	src = ft_atoi(current->right->data);
	if (dest != src && dup2(src, dest) == -1)
		exit(2);
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}

int				ft_exe_greatanddash(t_node *current, t_shell *shell)
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

int				ft_exe_lessgreat(t_node *current, t_shell *shell)
{
	int			dest;
	int			src;

	dest = current->left ? ft_atoi(current->left->data) : 0;
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	if ((src = open(current->right->data, O_RDWR)) == -1)
	{
		if ((src = open(current->right->data, O_RDWR | O_CREAT)) == -1)
			return (1);
		fchmod(src, 0644);
	}
	if (dest != src)
	{
		if (dup2(src, dest) == -1)
			exit(2);
		close(src);
	}
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}

int				ft_exe_dless(t_node *current, t_shell *shell)
{
	int			dest;
	int			pipefd[2];

	dest = current->left ? ft_atoi(current->left->data) : 0;
	if (pipe(pipefd) == -1)
		exit(2);
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	write(pipefd[1], current->right->right->data,
		ft_strlen(current->right->right->data));
	close(pipefd[1]);
	if (dest != pipefd[0])
	{
		if (dup2(pipefd[0], dest) == -1)
			exit(2);
		close(pipefd[0]);
	}
	if (current->redir)
		return (g_exetab[current->redir->token](current->redir, shell));
	return (0);
}

int				ft_exe_rbrace(t_node *current, t_shell *shell)
{
	t_tmpfd		*tmp;
	int			ret;

	shell->forked = 0;
	ret = 0;
	if (current->redir)
		ret = g_exetab[current->redir->token](current->redir, shell);
	tmp = shell->tmp_fds;
	shell->tmp_fds = NULL;
	if (!ret)
		ret = g_exetab[current->right->token](current->right, shell);
	ft_reset_tmp_fd(tmp);
	return (shell->retval = ret);
}

// char			*ft_expanse_replace(char *arg, int start, int len, char *by)
// {
// 	char		*result;
// 	int			count;

// 	count = start + ft_strlen(by) + ft_strlen(arg + start + len);
// 	if (!(result = (char *)malloc((count + 1) * sizeof(char))))
// 		return (NULL);
// 	ft_strncpy(result, arg, (size_t)start);
// 	ft_strcpy(result + start, by);
// 	ft_strcat(result + start, arg + start + len);
// 	free(arg);
// 	return (result);
// }

// int				ft_expanse_tilde(char **arg, int start, t_shell *shell)
// {
// 	int			i;
// 	char		*dir;
// 	struct passwd	*passwd;

// 	i = start + 1;
// 	if ((*arg)[i] >= '0' && (*arg)[i] <= '9')
// 		return (1);
// 	while ((*arg)[i] != '\0' && (*arg)[i] != '/' && (*arg)[i] != ':')
// 	{
// 		if (ft_isalnum((*arg)[i]) == 0 && (*arg)[i] != '_')
// 			return (1);
// 		i++;
// 	}
// 	if ((i - start) == 1)
// 	{
// 		dir = //RECUPERER VARIABLE HOME
// 		if (!dir && (!(passwd = getpwuid(getuid()))
// 			|| !(dir = ft_strdup(passwd->pw_dir))))
// 			return (-1);
// 	}
// 	else
// 	{
// 		if (!(dir = ft_strsub(*arg, start + 1, i - start - 1))
// 			|| !(passwd = getpwnam(dir)))
// 			return (-1);
// 		free(dir);
// 		if (!(passwd = ft_strdup(passwd->pw_dir)))
// 			return (-1);
// 	}
// 	if (!(arg = ft_expanse_replace(*arg, start, i, dir)))
// 		return (-1);
// 	i = ft_strlen(dir);
// 	free(dir);
// 	return (i);
// }

// int				ft_expanse_dollar_par(char **arg, int start, t_shell *shell)
// {
// 	int			pars;
// 	int			i;
// 	int			quote;

// 	pars = 1;
// 	i = start + 2;
// 	quote = '\0';
// 	while (pars)
// 	{
// 		if ((*arg)[i] == '\\')
// 			000

			
// 	}
// }

// int				ft_expanse_dollar(char **arg, int start, t_shell *shell,
// 				char quote)
// {
// 	if ((*arg)[start + 1] == '(')
// 		return (i = ft_expanse_dollar_par(arg, start, shell));
// 	else if ((*arg)[start + 1] == '{')
// 		return (i = ft_expanse_dollar_brace(arg, start, shell, quote));
// 	else
// 		return (ft_expanse_dollar_simple(arg, start, shell, quote));
// }

// int				ft_expanse_arg(char **arg, t_shell *shell)
// {
// 	char		quote;
// 	int			i;
// 	int			j;

// 	quote = '\0';
// 	i = 0;
// 	while ((*arg)[i])
// 	{
// 		j = 0;
// 		if ((*arg)[i] == quote)
// 			quote = '\0';
// 		else if (((*arg)[i] == '\'' || (*arg)[i] == '\"') && quote == '\0')
// 			quote = (*arg)[i];
// 		else if ((*arg)[i] == '\\')
// 			j = 2;
// 		else if ((*arg)[i] == '~' && i == 0)
// 			j = ft_expanse_tilde(arg, i, shell);
// 		else if ((*arg)[i] == '$' && quote != '\'')
// 			j = ft_expanse_dollar(arg, i, shell, quote);
// 		else if ((*arg)[i] == '`' && quote != '\'')
// 			j = ft_expanse_bquote(arg, i, shell);
// 		else
// 			j = 1;
// 		if (j < 0)
// 			return (-1);
// 		i = i + j;
// 	}
// 	return (0);
// }

char			**ft_expanse_command(t_node *current, t_shell *shell)
{
	char		**args;
	t_node		*words;
	int			i;

	(void)shell;
	i = 0;
	words = current->right;
	while (words)
	{
		words = words->right;
		i++;
	}
	if (!(args = (char **)malloc((i + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	words = current->right;
	while (words)
	{
		if (!(args[i] = ft_strdup(words->data)))
			return (NULL);
		words = words->right;
		i++;
	}
	args[i] = NULL;
	return (args);
}

int				ft_exe_command(t_node *current, t_shell *shell)
{
	t_joblist	*job;
	char		**args;
	int			status;

	if (!(args = ft_expanse_command(current, shell)))
		exit(2);
	if (!shell->forked)
	{
		if (!(job = ft_get_job(current, shell)))
			exit(2);
		job->process->path = args[0];
		job->process->args = args;
		ft_launch_job(job, shell);
		if (!shell->pgid && shell->foreground)
			tcsetpgrp(STDIN_FILENO, job->pgid);
		status = ft_wait_job(job);
		if (!shell->pgid && shell->foreground)
			tcsetpgrp(STDIN_FILENO, shell->pid);
		return ((shell->retval = WEXITSTATUS(job->process->status)));
	}
	if (current->redir
		&& g_exetab[current->redir->token](current->redir, shell))
		exit(1);
	execve(args[0], args, NULL);
	return ((shell->retval = 1));
}

void			ft_init(t_shell *shell)
{
	shell->pid = getpid();
	shell->pgid = getpgrp();
	shell->foreground = 0;
	if (isatty(STDIN_FILENO))
	{
		while (tcgetpgrp(STDIN_FILENO) != shell->pgid)
			kill(-shell->pgid, SIGTTIN);
		shell->pgid = 0;
		//signal(SIGINT, SIG_IGN);
  		signal(SIGQUIT, SIG_IGN);
   		signal(SIGTSTP, SIG_IGN);
   		signal(SIGTTIN, SIG_IGN);
   		signal(SIGTTOU, SIG_IGN);
		signal(SIGCHLD, SIG_DFL);
		setpgid(shell->pid, shell->pid);
		tcsetpgrp(STDIN_FILENO, shell->pid);
		tcgetattr(STDIN_FILENO, &(shell->term));
		shell->foreground = 1;
	}
	shell->forked = 0;
	shell->jobs = NULL;
	shell->retval = 0;
	shell->tmp_fds = NULL;
}

// int				main(int argc, char **argv, char **envp)
// {
// 	char		*input;
// 	void		*list;
// 	t_shell		shell;

// 	VOID;
// 	ft_init(&shell);
// 	if (get_next_line(0, &input) == -1)
// 		return (1);
// 	if (!(list = ft_lexer(&input)))
// 		return (1);
// 	if (!(list = ft_toklist_to_node(input, list)))
// 		return (1);
// 	free(input);
// 	if (!(list = ft_build_ast(list)))
// 		return (1);
// 	g_exetab[((t_node *)list)->token](list, &shell);
// 	return (0);
// }
