/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:15:15 by geargenc          #+#    #+#             */
/*   Updated: 2019/03/30 20:18:16 by geargenc         ###   ########.fr       */
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
	*process = (t_proclist){0, NULL, 0, NULL, NULL, NULL};
	if (current->token == PIPE)
	{
		process->command = current->left;
		process->next = ft_get_pipeline(current->right);
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

t_joblist		*ft_get_job(t_node *current, t_42sh *shell)
{
	t_joblist	*job;

	job = (t_joblist *)ft_malloc_exit(sizeof(t_joblist));
	job->process = ft_get_pipeline(current);
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

void			ft_launch_job(t_joblist *job, t_42sh *shell)
{
	t_proclist	*proc;
	int			pipefd[3];

	proc = job->process;
	ft_memset(pipefd, -1, sizeof(pipefd));
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

int				ft_any_stopped(t_joblist *job)
{
	t_proclist	*proc;

	proc = job->process;
	while (proc)
	{
		if (WIFSTOPPED(proc->status))
			return (1);
		proc = proc->next;
	}
	return (0);
}

int				ft_any_running(t_joblist *job)
{
	t_proclist	*proc;

	proc = job->process;
	while (proc)
	{
		if (!proc->status)
			return (1);
		proc = proc->next;
	}
	return (0);
}

int				ft_wait_job(t_joblist *job, int options)
{
	t_proclist	*proc;

	proc = job->process;
	while (proc && proc->next)
	{
		if (waitpid(proc->pid, &(proc->status), options) == 0)
			proc->status = 0;
		proc = proc->next;
	}
	if (waitpid(proc->pid, &(proc->status), options) == 0)
		proc->status = 0;
	return (proc->status);
}

char			*g_sigtab[] =
{
	"SIGERR",
	"SIGHUP",
	"SIGINT",
	"SIGQUIT",
	"SIGILL",
	"SIGTRAP",
	"SIGABRT",
	"SIGEMT",
	"SIGFPE",
	"SIGKILL",
	"SIGBUS",
	"SIGSEGV",
	"SIGSYS",
	"SIGPIPE",
	"SIGALRM",
	"SIGTERM",
	"SIGURG",
	"SIGSTOP",
	"SIGTSTP",
	"SIGCONT",
	"SIGCHLD",
	"SIGTTIN",
	"SIGTTOU",
	"SIGIO",
	"SIGXCPU",
	"SIGXFSZ",
	"SIGVTALRM",
	"SIGPROF",
	"SIGWINCH",
	"SIGINFO",
	"SIGUSR1",
	"SIGUSR2"
};

void			ft_report_status(t_joblist *job, int status)
{
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(job->num, 2);
	ft_putstr_fd("]  ", 2);
	if (WIFSTOPPED(status))
	{
		ft_putstr_fd("Stopped", 2);
		if (WSTOPSIG(status) > 0 && WSTOPSIG(status) <= 31)
		{
			ft_putstr_fd("(", 2);
			ft_putstr_fd(g_sigtab[WSTOPSIG(status)], 2);
			ft_putstr_fd(")", 2);
		}
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) > 0 && WTERMSIG(status) <= 31)
			ft_putstr_fd(g_sigtab[WTERMSIG(status)], 2);
	}
	else if (WIFEXITED(status))
		ft_putstr_fd("Done", 2);
	else
		ft_putstr_fd("Running", 2);
	ft_putstr_fd("\n", 2);
}

void			ft_push_job_back(t_joblist *job, t_42sh *shell)
{
	t_joblist	**tmp;

	tmp = &(shell->jobs);
	while (*tmp)
		tmp = &((*tmp)->next);
	*tmp = job;
}

int				ft_manage_job(t_joblist *job, t_42sh *shell)
{
	int			status;

	status = ft_wait_job(job, WUNTRACED);
	tcgetattr(STDIN_FILENO, &(job->term));
	if (shell->foreground)
		tcsetattr(STDIN_FILENO, TCSADRAIN, &(shell->term));
	if (!shell->pgid)
	{
		if (ft_any_stopped(job)
			|| (WIFSIGNALED(status) && WTERMSIG(status) == 2))
			ft_putstr_fd("\n", 2);
		if (WIFSTOPPED(status))
			ft_report_status(job, status);
		else if (ft_any_stopped(job))
			ft_report_status(job, _WSTOPPED);
		else if (WIFSIGNALED(status) && WTERMSIG(status) != 2)
			ft_report_status(job, status);
	}
	return (ft_get_retval(status));
}

int				ft_exe_pipe(t_node *current, t_42sh *shell)
{
	t_joblist	*job;

	shell->forked = 0;
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
	while ((cpy = dup(fd)) >= STDIN_FILENO && cpy <= STDERR_FILENO)
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

	if (!(tmp = (t_tmpfd *)ft_malloc_exit(sizeof(t_tmpfd))))
		exit(2);
	tmp->initial = fd;
	if ((tmp->cloexec = fcntl(fd, F_GETFD)) != -1)
	{
		if ((tmp->tmp = ft_dup_tmp_fd(fd)) == -1)
			exit(2);
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

int				ft_exe_great(t_node *current, t_42sh *shell)
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

int				ft_exe_less(t_node *current, t_42sh *shell)
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

int				ft_exe_rpar(t_node *current, t_42sh *shell)
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
		status = ft_wait_job(job, WUNTRACED);
		if (!shell->pgid && shell->foreground)
			tcsetpgrp(STDIN_FILENO, shell->pid);
		return (WEXITSTATUS(status));
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

int				ft_exe_lessand(t_node *current, t_42sh *shell)
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
	int			dest;
	int			src;

	if (!(ft_str_isdigit(current->right->data)))
		return (ft_exe_great(current, shell));
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

int				ft_exe_dless(t_node *current, t_42sh *shell)
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

int				ft_exe_command(t_node *current, t_42sh *shell)
{
	BUCKET_CONTENT	*bucket_entry;
	void			*exe;

	if (!(shell->argv->argv = ft_command_to_args(current, shell)))
		return ((shell->retval = 1));
	free_tab(shell->copy_env);
	shell->copy_env = list_to_tab(shell->env, shell->copy_env);
	if (shell->bin_dirs)
	{
		free_tab(shell->bin_dirs);
		shell->bin_dirs = NULL;
	}
	shell->valide_path = ft_getenv(shell->env, "PATH=", sizeof("PATH=") - 1);
	if (shell->valide_path)
	{
		if ((shell->bin_dirs = ft_strsplit(shell->valide_path, ':')) == NULL)
			print_error(_ENOMEM, 1);
	}
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
