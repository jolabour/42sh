/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 12:26:36 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/01 10:02:37 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

typedef struct	s_opt
{
	char		**argv;
	char		**after_opts;
	bool		available[256];
	bool		set[256];
}				t_opt;

void		ft_init_opts(t_opt *opt, char *available)
{
	ft_bzero(opt, sizeof(t_opt));
	while (available)
	{
		opt->available[(int)*available] = true;
		available++;
	}
}

int			ft_bad_opt(char *head, char opt)
{
	ft_putstr_fd(head, 2);
	ft_putstr_fd(": -", 2);
	ft_putchar_fd(opt, 2);
	ft_putstr_fd(": invalid option\n", 2);
	return (-1);
}

int			ft_get_opts(t_opt *opt, char **argv, char *error)
{
	int		i;

	opt->argv = argv;
	opt->after_opts = argv;
	while ((*(opt->after_opts))[0] == '-')
	{
		if (ft_strequ(*(opt->after_opts), "--"))
		{
			opt->after_opts++;
			return (0);
		}
		i = 1;
		while ((*(opt->after_opts))[i])
		{
			if (opt->available[(int)(*(opt->after_opts))[i]])
				opt->set[(int)(*(opt->after_opts[i]))] = true;
			else
				return (ft_bad_opt(error, (*(opt->after_opts))[i]));
			i++;
		}
		opt->after_opts++;
	}
	return (0);
}

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

void			ft_no_such_job(char *job)
{
	ft_putstr_fd("42sh: jobs: ", 2);
	ft_putstr_fd(job, 2);
	ft_putstr_fd(": no such job\n", 2);
}

void			ft_put_job_title(t_joblist *job, t_42sh *sh, int fd)
{
	ft_putstr_fd("[", fd);
	ft_putnbr_fd(job->num, fd);
	ft_putstr_fd("] ", fd);                          
	ft_putstr_fd(job == sh->current ? "+ " : "  ", fd);
}

int				ft_chars_in_int(int nbr)
{
	int			count;

	count = (nbr < 0) ? 2 : 1;
	while (nbr > 9 || nbr < -9)
	{
		count++;
		nbr = nbr / 10;
	}
	return (count);
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

int				ft_exited(int status, int fd)
{
	int			spaces;

	if (WIFEXITED(status))
	{
		ft_putstr_fd("Done", fd);
		spaces = 26;
		if (WEXITSTATUS(status))
		{
			ft_putstr_fd("(", fd);
			ft_putnbr(WEXITSTATUS(status));
			ft_putstr_fd(")", fd);
			spaces = 26 - ft_chars_in_int(WEXITSTATUS(status)) - 2;
		}
		if (spaces > 0 && spaces < 27)
			write(fd, "                          ", (size_t)spaces);
		return (1);
	}
	return (0);
}

int				ft_signaled(int status, int fd)
{
	int			sig;

	if (WIFSIGNALED(status))
	{
		sig = (WTERMSIG(status) > 0 && WTERMSIG(status) < 32)
			? WTERMSIG(status) : 0;
		ft_putstr_fd(g_sigtab[sig], fd);
		write(fd, "                              ",
			30 - ft_strlen(g_sigtab[sig]));
		return (1);
	}
	return (0);
}

int				ft_stopped_long(int status, int fd)
{
	int			sig;

	if (WIFSTOPPED(status))
	{
		sig = (WSTOPSIG(status) > 0 && WSTOPSIG(status) < 32)
			? WSTOPSIG(status) : 0;
		ft_putstr_fd(g_sigtab[sig], fd);
		write(fd, "                              ",
			30 - ft_strlen(g_sigtab[sig]));
		return (1);
	}
	return (0);
}

int				ft_stopped(int status, int fd)
{
	int			spaces;

	if (WIFSTOPPED(status))
	{
		ft_putstr_fd("Stopped", fd);
		spaces = 23;
		if (WSTOPSIG(status) > 0 && WSTOPSIG(status) < 32)
		{
			ft_putstr_fd("(", fd);
			ft_putstr_fd(g_sigabrevtab[WSTOPSIG(status)], fd);
			ft_putstr_fd(")", fd);
			spaces = 23 - ft_strlen(g_sigabrevtab[WSTOPSIG(status)]) - 2;
		}
		if (spaces > 0 && spaces < 24)
			write(fd, "                       ", spaces);
		return (1);
	}
	return (0);
}

int				ft_running(int status, int fd)
{
	(void)status;
	ft_putstr_fd("Running                       ", fd);
	return (1);
}

void			ft_print_badtoken(t_node *command, int fd)
{
	(void)command;
	(void)fd;
}

void			ft_print_sep(t_node *command, int fd)
{
	g_printtab[command->left->token](command->left, fd);
	ft_putstr_fd(" ", fd);
	ft_putstr_fd(command->data, fd);
	if (command->right)
	{
		ft_putstr_fd(" ", fd);
		g_printtab[command->right->token](command->right, fd);
	}
}

void			ft_print_redir(t_node *command, int fd)
{
	if (command->left)
		ft_putstr_fd(command->left->data, fd);
	ft_putstr_fd(command->data, fd);
	ft_putstr_fd(" ", fd);
	ft_putstr_fd(command->right->data, fd);
	if (command->redir)
	{
		ft_putstr_fd(" ", fd);
		g_printtab[command->redir->token](command->redir, fd);
	}
}

void			ft_print_par(t_node *command, int fd)
{
	ft_putstr_fd("( ", fd);
	g_printtab[command->right->token](command->right, fd);
	ft_putstr_fd(" )", fd);
	if (command->redir)
	{
		ft_putstr_fd(" ", fd);
		g_printtab[command->redir->token](command->redir, fd);
	}
}

void			ft_print_redir_and(t_node *command, int fd)
{
	if (command->left)
		ft_putstr_fd(command->left->data, fd);
	ft_putstr_fd(command->data, fd);
	ft_putstr_fd(command->right->data, fd);
	if (command->redir)
	{
		ft_putstr_fd(" ", fd);
		g_printtab[command->redir->token](command->redir, fd);
	}
}

void			ft_print_redir_close(t_node *command, int fd)
{
	if (command->left)
		ft_putstr_fd(command->left->data, fd);
	ft_putstr_fd(command->data, fd);
	if (command->redir)
	{
		ft_putstr_fd(" ", fd);
		g_printtab[command->redir->token](command->redir, fd);
	}
}

void			ft_print_brace(t_node *command, int fd)
{
	ft_putstr_fd("{ ", fd);
	g_printtab[command->right->token](command->right, fd);
	ft_putstr_fd(" }", fd);
	if (command->redir)
	{
		ft_putstr_fd(" ", fd);
		g_printtab[command->redir->token](command->redir, fd);
	}
}

void			ft_print_assigns(t_node *command, int fd)
{
	t_node		*node;

	node = command->left;
	while (node)
	{
		ft_putstr_fd(node->data, fd);
		if (node->left || command->right || command->redir)
			ft_putstr_fd(" ", fd);
		node = node->left;
	}
}

void			ft_print_words(t_node *command, int fd)
{
	t_node		*node;

	node = command->right;
	while (node)
	{
		ft_putstr_fd(node->data, fd);
		if (node->right || command->redir)
			ft_putstr_fd(" ", fd);
		node = node->right;
	}
}

void			ft_print_command(t_node *command, int fd)
{
	if (command->left)
		ft_print_assigns(command, fd);
	if (command->right)
		ft_print_words(command, fd);
	if (command->redir)
		g_printtab[command->redir->token](command->redir, fd);
}

void			ft_report_job_long(t_joblist *job, t_42sh *sh, int fd)
{
	t_proclist	*proc;

	proc = job->process;
	while (proc)
	{
		proc == job->process ? ft_put_job_title(job, sh, fd)
			: ft_putstr_fd("     ", fd);
		ft_putnbr_fd(proc->pid, fd);
		ft_putstr_fd(" ", fd);
		if (!(ft_exited(proc->status, fd) || ft_signaled(proc->status, fd)
			|| ft_stopped_long(proc->status, fd)))
			ft_running(proc->status, fd);
		ft_putstr_fd(proc == job->process ? "  " : "| ", fd);
		g_printtab[proc->command->token](proc->command, fd);
		ft_putstr_fd("\n", fd);
		proc = proc->next;
	}
}

void			ft_report_job_pgid(t_joblist *job, t_42sh *sh, int fd)
{
	(void)sh;
	ft_putnbr_fd(job->pgid, fd);
	ft_putstr_fd("\n", fd);
}

void			ft_report_job_def(t_joblist *job, t_42sh *sh, int fd)
{
	t_proclist	*last;

	last = job->process;
	if (last)
		while (last->next)
			last = last->next;
	ft_put_job_title(job, sh, fd);
	if (ft_any_running(job))
		ft_running(0, fd);
	else if (!ft_stopped(last->status, fd))
	{
		if (ft_any_stopped(job))
			ft_stopped(_WSTOPPED, fd);
		else if (!(ft_exited(last->status, fd)
			|| ft_signaled(last->status, fd)))
			write(fd, "                              ", 30);
	}
	g_printtab[job->command->token](job->command, fd);
	ft_putstr_fd("\n", 2);
}

void			ft_report_job(t_opt *opt, t_joblist *job, t_42sh *sh)
{
	if (opt && opt->set['l'])
		ft_report_job_long(job, sh, STDOUT_FILENO);
	else if (opt && opt->set['p'])
		ft_report_job_pgid(job, sh, STDOUT_FILENO);
	else
		ft_report_job_def(job, sh, STDOUT_FILENO);
}

void			ft_jobs(t_opt *opt, t_42sh *sh)
{
	t_joblist	*jobs;

	if (!(*(opt->after_opts)))
	{
		jobs = sh->jobs;
		while (jobs)
			ft_report_job(opt, jobs, sh);
	}
	else while ((*(opt->after_opts)))
	{
		jobs = NULL;
		if ((*(opt->after_opts))[0] == '+')
			jobs = sh->current;
		else if (ft_str_isdigit((*(opt->after_opts))))
			jobs = ft_search_job(sh->jobs, ft_atoi((*(opt->after_opts))));
		if (jobs == NULL)
		{
			ft_no_such_job((*(opt->after_opts)));
			sh->retval = 1;
		}
		else
			ft_report_job(opt, jobs, sh);
		opt->after_opts++;
	}
}

void		builtin_jobs(t_42sh *sh)
{
	t_opt	opt;

	sh->retval = 0;
	ft_init_opts(&opt, "lp");
	if (ft_get_opts(&opt, sh->argv->argv, "42sh: jobs"))
	{
		ft_putstr_fd("jobs: usage: jobs [-lp] [jobspec ...]\n", 2);
		sh->retval = 2;
	}
	else
		ft_jobs(&opt, sh);
}
