/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:15:15 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/04 23:59:14 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"


int				ft_exe_badtoken(t_node *current, t_42sh *shell)
{
	(void)current;
	(void)shell;
	return (-1);
}

t_proclist		*ft_get_pipeline(t_node *current)
{
	t_proclist	*process;

	process = (t_proclist *)ft_malloc_exit(sizeof(t_proclist));
	*process = (t_proclist){0, NULL, NULL, 0, false, NULL, NULL, NULL};
	if (current->token == PIPE)
	{
		process->command = current->left;
		process->cmdline = g_cmdlinetab[current->left->token](current->left);
		process->next = ft_get_pipeline(current->right);
	}
	else
	{
		process->command = current;
		process->cmdline = g_cmdlinetab[current->token](current);
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

void			ft_push_job_back(t_joblist *job, t_42sh *shell)
{
	t_joblist	**tmp;

	tmp = &(shell->jobs);
	while (*tmp)
		tmp = &((*tmp)->next);
	*tmp = job;
}

t_joblist		*ft_get_job(t_node *current, t_42sh *shell)
{
	t_joblist	*job;

	job = (t_joblist *)ft_malloc_exit(sizeof(t_joblist));
	job->process = ft_get_pipeline(current);
	if (shell->pgid)
		job->pgid = shell->pgid;
	else
		job->pgid = 0;
	job->cmdline = g_cmdlinetab[current->token](current);
	job->next = NULL;
	job->num = ft_get_job_number(shell->jobs);
	job->stopped = false;
	tcgetattr(STDIN_FILENO, &(job->term));
	if (!shell->current)
		shell->current = job;
	ft_push_job_back(job, shell);
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

int				ft_exe_file(t_node *current, t_42sh *shell,
				char *path, char **args)
{
	t_joblist	*job;

	if (!shell->forked)
	{
		job = ft_get_job(current, shell);
		job->process->path = path;
		job->process->args = args;
		ft_launch_job(job, shell);
		if (!shell->pgid && shell->foreground)
			tcsetpgrp(STDIN_FILENO, job->pgid);
		shell->retval = ft_manage_job(job, shell);
		if (!shell->pgid && shell->foreground)
			tcsetpgrp(STDIN_FILENO, shell->pid);
		return (shell->retval);
	}
	if (current->redir
		&& g_exetab[current->redir->token](current->redir, shell))
		exit(1);
	execve(path, args, shell->copy_env);
	exit((shell->retval = 1));
}

void			ft_launch_process(t_proclist *proc, t_42sh *shell,
				int pipefd[3], pid_t pgid)
{
	shell->jobs = NULL;
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
		ft_exe_file(proc->command, shell, proc->path, proc->args);
	exit(g_exetab[proc->command->token](proc->command, shell));
}

int				ft_pipe_exit(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("42sh: pipe: Error\n", 2);
		exit(2);
	}
	return (0);
}

pid_t			ft_fork_exit(void)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("42sh: fork: Error\n", 2);
		exit(2);
	}
	return (pid);
}

int				ft_dup_exit(int fd)
{
	int			ret;

	if (fcntl(fd, F_GETFD) == -1)
		return (-1);
	if ((ret = dup(fd)) == -1)
	{
		ft_putstr_fd("42sh: dup: Error\n", 2);
		exit(2);
	}
	return (ret);
}

int				ft_dup2_exit(int fd1, int fd2)
{
	int			ret;

	if (fcntl(fd1, F_GETFD) == -1)
		return (-1);
	if ((ret = dup2(fd1, fd2)) == -1)
	{
		ft_putstr_fd("42sh: dup: Error\n", 2);
		exit(2);
	}
	return (ret);
}

void			ft_launch_job(t_joblist *job, t_42sh *shell)
{
	t_proclist	*proc;
	int			pipefd[3];

	proc = job->process;
	ft_memset(pipefd, -1, sizeof(pipefd));
	while (proc)
	{
		if (proc->next)
			ft_pipe_exit(pipefd);
		if (!proc->next)
			pipefd[1] = -1;
		proc->pid = ft_fork_exit();
		if (!proc->pid)
			ft_launch_process(proc, shell, pipefd, job->pgid);
		if (job->pgid == 0)
			job->pgid = proc->pid;
		if (!shell->foreground)
			shell->last_bg = proc->pid;
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
	ft_putstr("\nWIFCONTINUED: ");
	ft_putnbr(WIFCONTINUED(status));
	ft_putstr("\nWCOREDUMP: ");
	ft_putnbr(WCOREDUMP(status));
	ft_putstr("\nisatty: ");
	ft_putnbr(isatty(1));
	ft_putstr("\n");
}

int				ft_get_retval(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	return (-1);
}

int				ft_wait_job(t_joblist *job, int options, t_42sh *shell)
{
	t_proclist	*proc;
	int 		status;

	proc = job->process;
	while (proc)
	{
		if (!proc->complete && waitpid(proc->pid, &(proc->status), options))
		{
			if (WIFSTOPPED(proc->status))
				shell->current = job;
			else if (WIFCONTINUED(proc->status))
			{
				proc->status = 0;
				job->stopped = false;
			}
			else
				proc->complete = true;
		}
		status = proc->status;
		proc = proc->next;
	}
	return (status);
}

t_joblist		*ft_get_last_job(t_joblist *jobs)
{
	if (jobs)
		while (jobs->next)
			jobs = jobs->next;
	return (jobs);
}

void			ft_remove_proc(t_proclist *proc)
{
	//int			i;

	free(proc->cmdline);
	if (proc->path)
		free(proc->path);
	// if (proc->args)
	// {
	// 	i = 0;
	// 	while (proc->args[i])
	// 	{
	// 		free(proc->args[i]);
	// 		i++;
	// 	}
	// 	free(proc->args);
	// }
	free(proc);
}

void			ft_remove_job(t_joblist *job, t_42sh *shell)
{
	t_joblist	**tmp_job;
	t_proclist	*tmp_proc;

	tmp_job = &(shell->jobs);
	while (*tmp_job)
	{
		if (*tmp_job == job)
			*tmp_job = (*tmp_job)->next;
		else
			tmp_job = &((*tmp_job)->next);
	}
	if (job == shell->current)
		shell->current = ft_get_last_job(shell->jobs);
	while (job->process)
	{
		tmp_proc = job->process;
		job->process = job->process->next;
		ft_remove_proc(tmp_proc);
	}
	free(job->cmdline);
	free(job);
}

void			ft_check_job(t_joblist *job, t_42sh *shell)
{
	ft_wait_job(job, WUNTRACED | WNOHANG | WCONTINUED, shell);
	if (!ft_any_running(job))
	{
		if (job->stopped ? !ft_any_stopped(job) : true)
			ft_report_job_def(job, shell, STDERR_FILENO);
		job->stopped = true;
		if (!ft_any_stopped(job))
			ft_remove_job(job, shell);
	}
	else
		job->stopped = false;
}

void			ft_check_jobs(t_42sh *shell)
{
	t_joblist	*jobs;
	t_joblist	*next;

	jobs = shell->jobs;
	while (jobs)
	{
		next = jobs->next;
		ft_check_job(jobs, shell);
		jobs = next;
	}
}

int				ft_manage_job(t_joblist *job, t_42sh *shell)
{
	int			status;

	status = ft_wait_job(job, WUNTRACED, shell);
	tcgetattr(STDIN_FILENO, &(job->term));
	if (!shell->pgid && shell->foreground)
	{
		tcsetpgrp(STDIN_FILENO, shell->pid);
		tcsetattr(STDIN_FILENO, TCSADRAIN, &(shell->term));
	}
	if (!shell->pgid)
	{
		if (ft_any_stopped(job))
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			ft_report_job_def(job, shell, STDERR_FILENO);
		}
		else if (WIFSIGNALED(status))
		{
			ft_putstr_fd(g_sigtab[WTERMSIG(status) > 0 && WTERMSIG(status)
				< 32 ? WTERMSIG(status) : 0], STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
		}
	}
	ft_any_stopped(job) ? job->stopped = true : ft_remove_job(job, shell);
	return (ft_get_retval(status));
}

int				ft_exe_pipe(t_node *current, t_42sh *shell)
{
	t_joblist	*job;

	shell->forked = 0;
	job = ft_get_job(current, shell);
	ft_launch_job(job, shell);
	if (!shell->pgid && shell->foreground)
		tcsetpgrp(STDIN_FILENO, job->pgid);
	return (shell->retval = ft_manage_job(job, shell));
}

void			ft_print_bg(t_joblist *job, t_42sh *shell)
{
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(job->num, 2);
	ft_putstr_fd("] ", 2);
	ft_putnbr_fd(shell->last_bg, 2);
	ft_putstr_fd("\n", 2);
}

int				ft_exe_and(t_node *current, t_42sh *shell)
{
	t_joblist	*job;
	int			foreground;

	// if (shell->pgid)
	// 	return (ft_exe_semi(current, shell));
	shell->forked = 0;
	job = ft_get_job(current->left, shell);
	foreground = shell->foreground;
	shell->foreground = 0;
	ft_launch_job(job, shell);
	shell->foreground = foreground;
	if (!(shell->pgid))
		ft_print_bg(job, shell);
	shell->retval = 0;
	if (current->right)
		shell->retval = g_exetab[current->right->token](current->right, shell);
	return (shell->retval);
}

int				ft_exe_semi(t_node *current, t_42sh *shell)
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
	bool		denied[3];

	denied[STDIN_FILENO] = false;
	denied[STDOUT_FILENO] = false;
	denied[STDERR_FILENO] = false;
	while ((cpy = ft_dup_exit(fd)) >= STDIN_FILENO && cpy <= STDERR_FILENO)
		denied[cpy] = true;
	if (denied[STDIN_FILENO])
		close(STDIN_FILENO);
	if (denied[STDOUT_FILENO])
		close(STDOUT_FILENO);
	if (denied[STDERR_FILENO])
		close(STDERR_FILENO);
	return (cpy);
}

void			ft_build_tmp_fd(int fd, t_tmpfd **begin)
{
	t_tmpfd		*tmp;

	tmp = (t_tmpfd *)ft_malloc_exit(sizeof(t_tmpfd));
	tmp->initial = fd;
	if ((tmp->cloexec = fcntl(fd, F_GETFD)) != -1)
	{
		tmp->tmp = ft_dup_tmp_fd(fd);
		fcntl(tmp->tmp, F_SETFD, FD_CLOEXEC);
	}
	else
		tmp->tmp = -1;
	tmp->next = *begin;
	*begin = tmp;
}

void			ft_reset_tmp_fd(t_tmpfd *begin)
{
	t_tmpfd		*tmp;

	while (begin)
	{
		if (begin->tmp == -1)
			close(begin->initial);
		else
		{
			if (dup2(begin->tmp, begin->initial) == -1)
				exit(2);
			close(begin->tmp);
			fcntl(begin->initial, F_SETFD, begin->cloexec);
		}
		tmp = begin;
		begin = begin->next;
		free(tmp);
	}
}

int				ft_open_error(char *path, int options, char *unexp)
{
	int			fd;
	struct stat	sstat;

	if ((fd = open(path, options)) == -1)
	{
		ft_putstr_fd("42sh: ", STDERR_FILENO);
		ft_putstr_fd(unexp, STDERR_FILENO);
		if (access(path, F_OK))
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		else if (stat(path, &sstat))
			ft_putstr_fd(": Unknown error (stat)\n", STDERR_FILENO);
		else if (S_ISDIR(sstat.st_mode))
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		else if ((((options & O_RDONLY) || (options & O_RDWR))
			&& access(path, R_OK)) || (((options & O_WRONLY)
			|| (options & O_RDWR)) && access(path, W_OK)))
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		else
			ft_putstr_fd(": Unknown error. For more informations please feel "
				"free to make a request at errno@missing.42.fr\n",
				STDERR_FILENO);
		free(path);
	}
	return (fd);
}

int				ft_exe_great(t_node *current, t_42sh *shell)
{
	char		*path;
	int			dest;
	int			src;

	dest = current->left ? ft_atoi(current->left->data) : 1;
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	path = ft_simple_expanse(current->right->data, shell);
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
	path = ft_simple_expanse(current->right->data, shell);
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

int				ft_exe_rpar(t_node *current, t_42sh *shell)
{
	t_joblist	*job;

	if (!shell->forked)
	{
		if (!(job = ft_get_job(current, shell)))
			exit(2);
		ft_launch_job(job, shell);
		if (!shell->pgid && shell->foreground)
			tcsetpgrp(STDIN_FILENO, job->pgid);
		shell->retval = ft_manage_job(job, shell);
		if (!shell->pgid && shell->foreground)
			tcsetpgrp(STDIN_FILENO, shell->pid);
		return (shell->retval);
	}
	if (current->redir
		&& g_exetab[current->redir->token](current->redir, shell))
		exit(1);
	exit(g_exetab[current->right->token](current->right, shell));
}

int				ft_exe_and_if(t_node *current, t_42sh *shell)
{
	int			ret;

	shell->forked = 0;
	if ((ret = g_exetab[current->left->token](current->left, shell)))
		return (ret);
	return (g_exetab[current->right->token](current->right, shell));
}

int				ft_exe_or_if(t_node *current, t_42sh *shell)
{
	int			ret;

	shell->forked = 0;
	if ((ret = g_exetab[current->left->token](current->left, shell)) < 1)
		return (ret);
	return (g_exetab[current->right->token](current->right, shell));
}

int				ft_exe_dgreat(t_node *current, t_42sh *shell)
{
	char		*path;
	int			dest;
	int			src;

	dest = current->left ? ft_atoi(current->left->data) : 1;
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	path = ft_simple_expanse(current->right->data, shell);
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

int				ft_ambigous_error(char *fd, char *unexp)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putstr_fd(unexp, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
	free(fd);
	return (1);
}

int				ft_badfd_error(char *fd, char *unexp)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putstr_fd(unexp, STDERR_FILENO);
	ft_putstr_fd(": Bad file descriptor\n", STDERR_FILENO);
	free(fd);
	return (1);
}

int				ft_exe_lessand(t_node *current, t_42sh *shell)
{
	char		*fd;
	int			dest;
	int			src;
	int			ret;

	dest = current->left ? ft_atoi(current->left->data) : 0;
	fd = ft_simple_expanse(current->right->data, shell);
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

	dest = current->left ? ft_atoi(current->left->data) : 0;
	fd = ft_simple_expanse(current->right->data, shell);
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

int				ft_exe_lessgreat(t_node *current, t_42sh *shell)
{
	char		*path;
	int			dest;
	int			src;

	path = ft_simple_expanse(current->right->data, shell);
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

int				ft_exe_dless(t_node *current, t_42sh *shell)
{
	int			dest;
	int			pipefd[2];
	char		*heredoc;

	dest = current->left ? ft_atoi(current->left->data) : 0;
	ft_pipe_exit(pipefd);
	if (!shell->forked)
		ft_build_tmp_fd(dest, &(shell->tmp_fds));
	heredoc = ft_simple_expanse(current->right->right->data, shell);
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

int				ft_exe_rbrace(t_node *current, t_42sh *shell)
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

void			(*ft_isbuiltin(char *word))(t_42sh *)
{
	int			i;

	i = 0;
	while (g_bttab[i].name && !ft_strequ(g_bttab[i].name, word))
		i++;
	return (g_bttab[i].f);
}

int				ft_exe_builtin(t_node *current, t_42sh *shell,
				void (*f)(t_42sh *))
{
	t_tmpfd		*tmp;

	if (current->redir
		&& g_exetab[current->redir->token](current->redir, shell))
		return (1);
	tmp = shell->tmp_fds;
	shell->tmp_fds = NULL;
	f(shell);
	ft_reset_tmp_fd(tmp);
	return (shell->retval);
}

void			ft_add_tmp_env(char *var, char *value, t_42sh *shell)
{
	char		**newenv;
	int			i;

	i = 0;
	while (shell->copy_env[i] && !ft_strnequ(var, shell->copy_env[i],
		ft_strlen(var)))
		i++;
	if (shell->copy_env[i])
	{
		free(shell->copy_env[i]);
		shell->copy_env[i] = ft_strjoin(var, value);
	}
	else
	{
		newenv = (char **)ft_malloc_exit((i + 2) * sizeof(char *));
		i = -1;
		while (shell->copy_env[++i])
			newenv[i] = shell->copy_env[i];
		newenv[i] = ft_strjoin(var, value);
		newenv[i + 1] = NULL;
		free(shell->copy_env);
		shell->copy_env = newenv;
	}
}

int				ft_tmp_assigns(t_node *current, t_42sh *shell)
{
	char		*var;
	char		*value;

	current = current->left;
	while (current)
	{
		var = ft_strchr(current->data, '=');
		value = ft_simple_expanse(var + 1, shell);
		var = ft_strsub(current->data, 0, var - current->data + 1);
		ft_add_tmp_env(var, value, shell);
		free(var);
		free(value);
		current = current->left;
	}
	return (0);
}

int				ft_sustained_assigns(t_node *current, t_42sh *shell)
{
	char		*var;
	char		*value;

	current = current->left;
	while (current)
	{
		var = ft_strchr(current->data, '=');
		value = ft_simple_expanse(var + 1, shell);
		var = ft_strsub(current->data, 0, var - current->data + 1);
		var = ft_strjoinfree(var, value, 3);
		check_local_variable(shell, var);
		free(var);
		current = current->left;
	}
	return (0);
}

int				ft_assigns(t_node *current, t_42sh *shell)
{
	free_tab(shell->copy_env);
	shell->copy_env = list_to_tab(shell->env, shell->copy_env);
	if (current->left)
	{
		if (!current->right)
			return (ft_sustained_assigns(current, shell));
		else
			return (ft_tmp_assigns(current, shell));
	}
	return (0);
}

int				ft_exe_command(t_node *current, t_42sh *shell)
{
	BUCKET_CONTENT	*bucket_entry;
	void			*exe;

	if (!(shell->argv->argv = ft_command_to_args(current, shell)))
		return ((shell->retval = 1));
	if (ft_assigns(current, shell))
		return ((shell->retval = 1));
	if (!current->right)
		return ((shell->retval = 0));
	if (shell->bin_dirs)
	{
		free_tab(shell->bin_dirs);
		shell->bin_dirs = NULL;
	}
	shell->valide_path = ft_getenv(shell->env, "PATH=", sizeof("PATH=") - 1);
	if (shell->valide_path)
		shell->bin_dirs = ft_strsplit(shell->valide_path, ':');
	exe = ft_isbuiltin(shell->argv->argv[0]);
	if (exe)
		return ((shell->retval = ft_exe_builtin(current, shell, exe)));
	if ((bucket_entry = ht_lookup(shell->argv->argv[0], &shell->hashtable)) != NULL)
		shell->valide_path = ft_strdup(bucket_entry->path);
	else
	{
		shell->valide_path = check_access(shell, 0);
		if (shell->valide_path == NULL)
		{
			ft_putendl("donne un binaire gorille");
			return ((shell->retval = 127));
		}
		if (shell->argv->argv[0][0] != '/')
			ht_insert(shell->valide_path, shell->argv->argv[0], &shell->hashtable);
	}
	struct stat info;
	stat(shell->valide_path, &info);
	if (access(shell->valide_path, X_OK) == -1 || ((S_ISREG(info.st_mode)) != 1))
	{
		ft_putendl("t'as pas les droits victimes");
		ft_strdel(&shell->valide_path);
		return ((shell->retval = 126));
	}
	return (ft_exe_file(current, shell, shell->valide_path, shell->argv->argv));
}

void			ft_init(t_42sh *shell)
{
	shell->pid = getpid();
	shell->pgid = getpgrp();
	shell->foreground = 0;
	if (isatty(STDIN_FILENO))
	{
		while (tcgetpgrp(STDIN_FILENO) != shell->pgid)
			kill(-shell->pgid, SIGTTIN);
		shell->pgid = 0;
		signal(SIGINT, SIG_IGN);
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
