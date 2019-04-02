/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 12:26:36 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/02 19:04:43 by geargenc         ###   ########.fr       */
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
	while (*available)
	{
		opt->available[(int)*available] = true;
		available++;
	}
}

int			ft_bad_opt(char *head, char opt)
{
	ft_putstr_fd(head, STDERR_FILENO);
	ft_putstr_fd(": -", STDERR_FILENO);
	ft_putchar_fd(opt, STDERR_FILENO);
	ft_putstr_fd(": invalid option\n", STDERR_FILENO);
	return (-1);
}

int			ft_get_opts(t_opt *opt, char **argv, char *error)
{
	int		i;

	opt->argv = argv;
	opt->after_opts = argv;
	while (*(opt->after_opts) && (*(opt->after_opts))[0] == '-'
		&& (*(opt->after_opts))[1])
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
				opt->set[(int)(*(opt->after_opts))[i]] = true;
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

void			ft_no_such_job(char *job, char *builtin)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	if (builtin)
	{
		ft_putstr_fd(builtin, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(job ? job : "current", STDERR_FILENO);
	ft_putstr_fd(": no such job\n", STDERR_FILENO);
}

void			ft_put_job_title(t_joblist *job, t_42sh *sh, int fd)
{
	ft_putstr_fd("[", fd);
	ft_putnbr_fd(job->num, fd);
	ft_putstr_fd("]", fd);                          
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
		if (!(proc->complete || WIFSTOPPED(proc->status)))
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

char			*ft_cmdline_badtoken(t_node *command)
{
	(void)command;
	return (ft_strdup(""));
}

char			*ft_cmdline_sep(t_node *command)
{
	char		*line;

	line = g_cmdlinetab[command->left->token](command->left);
	line = ft_strjoinfree(line, " ", 1);
	line = ft_strjoinfree(line, command->data, 1);
	if (command->right)
	{
		line = ft_strjoinfree(line, " ", 1);
		line = ft_strjoinfree(line,
			g_cmdlinetab[command->right->token](command->right), 3);
	}
	return (line);
}

char			*ft_cmdline_redir(t_node *command)
{
	char		*line;

	line = ft_strdup(command->left ? command->left->data : "");
	line = ft_strjoinfree(line, command->data, 1);
	line = ft_strjoinfree(line, " ", 1);
	line = ft_strjoinfree(line, command->right->data, 1);
	if (command->redir)
	{
		line = ft_strjoinfree(line, " ", 1);
		line = ft_strjoinfree(line,
			g_cmdlinetab[command->redir->token](command->redir), 3);
	}
	return (line);
}

char			*ft_cmdline_par(t_node *command)
{
	char		*line;

	line = ft_strdup("( ");
	line = ft_strjoinfree(line,
		g_cmdlinetab[command->right->token](command->right), 3);
	line = ft_strjoinfree(line, " )", 1);
	if (command->redir)
	{
		line = ft_strjoinfree(line, " ", 1);
		line = ft_strjoinfree(line,
			g_cmdlinetab[command->redir->token](command->redir), 3);
	}
	return (line);
}

char			*ft_cmdline_redir_and(t_node *command)
{
	char		*line;

	line = ft_strdup(command->left ? command->left->data : "");
	line = ft_strjoinfree(line, command->data, 1);
	line = ft_strjoinfree(line, command->right->data, 1);
	if (command->redir)
	{
		line = ft_strjoinfree(line, " ", 1);
		line = ft_strjoinfree(line,
			g_cmdlinetab[command->redir->token](command->redir), 3);
	}
	return (line);
}

char			*ft_cmdline_redir_close(t_node *command)
{
	char		*line;

	line = ft_strdup(command->left ? command->left->data : "");
	line = ft_strjoinfree(line, command->data, 1);
	if (command->redir)
	{
		line = ft_strjoinfree(line, " ", 1);
		line = ft_strjoinfree(line,
			g_cmdlinetab[command->redir->token](command->redir), 3);
	}
	return (line);
}

char			*ft_cmdline_brace(t_node *command)
{
	char		*line;

	line = ft_strdup("{ ");
	line = ft_strjoinfree(line,
		g_cmdlinetab[command->right->token](command->right), 3);
	line = ft_strjoinfree(line, " }", 1);
	if (command->redir)
	{
		line = ft_strjoinfree(line, " ", 1);
		line = ft_strjoinfree(line,
			g_cmdlinetab[command->redir->token](command->redir), 3);
	}
	return (line);
}

char			*ft_cmdline_assigns(t_node *command)
{
	char		*line;
	t_node		*node;

	line = ft_strdup("");
	node = command->left;
	while (node)
	{
		line = ft_strjoinfree(line, node->data, 1);
		if (node->left || command->right || command->redir)
			line = ft_strjoinfree(line, " ", 1);
		node = node->left;
	}
	return (line);
}

char			*ft_cmdline_words(t_node *command)
{
	char		*line;
	t_node		*node;

	line = ft_strdup("");
	node = command->right;
	while (node)
	{
		line = ft_strjoinfree(line, node->data, 1);
		if (node->right || command->redir)
			line = ft_strjoinfree(line, " ", 1);
		node = node->right;
	}
	return (line);
}

char			*ft_cmdline_command(t_node *command)
{
	char		*line;

	line = ft_strdup("");
	if (command->left)
		line = ft_strjoinfree(line, ft_cmdline_assigns(command), 3);
	if (command->right)
		line = ft_strjoinfree(line, ft_cmdline_words(command), 3);
	if (command->redir)
		line = ft_strjoinfree(line,
			g_cmdlinetab[command->redir->token](command->redir), 3);
	return(line);
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
		ft_putstr_fd(proc->cmdline, fd);
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
	ft_putstr_fd(job->cmdline, fd);
	ft_putstr_fd("\n", fd);
}

void			ft_report_job(t_opt *opt, t_joblist *job, t_42sh *sh)
{
	ft_wait_job(job, WUNTRACED | WNOHANG | WCONTINUED, sh);
	if (opt && opt->set['l'])
		ft_report_job_long(job, sh, STDOUT_FILENO);
	else if (opt && opt->set['p'])
		ft_report_job_pgid(job, sh, STDOUT_FILENO);
	else
		ft_report_job_def(job, sh, STDOUT_FILENO);
	if (!(ft_any_running(job) || ft_any_stopped(job)))
					ft_remove_job(job, sh);
}

void			ft_report_all_jobs(t_opt *opt, t_42sh *sh)
{
	t_joblist	*jobs;

	jobs = sh->jobs;
	while (jobs)
	{
		ft_report_job(opt, jobs, sh);
		jobs = jobs->next;
	}
}

void			ft_jobs(t_opt *opt, t_42sh *sh)
{
	t_joblist	*jobs;

	if (!(*(opt->after_opts)))
		ft_report_all_jobs(opt, sh);
	else
		while ((*(opt->after_opts)))
		{
			jobs = NULL;
			if ((*(opt->after_opts))[0] == '+')
				jobs = sh->current;
			else if (ft_str_isdigit((*(opt->after_opts))))
				jobs = ft_search_job(sh->jobs, ft_atoi((*(opt->after_opts))));
			if (jobs == NULL)
			{
				ft_no_such_job((*(opt->after_opts)), "jobs");
				sh->retval = 1;
			}
			else
				ft_report_job(opt, jobs, sh);
			opt->after_opts++;
		}
}

void			builtin_jobs(t_42sh *sh)
{
	t_opt		opt;

	sh->retval = 0;
	ft_init_opts(&opt, "lp");
	if (ft_get_opts(&opt, sh->argv->argv + 1, "42sh: jobs"))
	{
		ft_putstr_fd("jobs: usage: jobs [-lp] [jobspec ...]\n", STDERR_FILENO);
		sh->retval = 2;
	}
	else
		ft_jobs(&opt, sh);
}

void			ft_fg(t_joblist *job, t_42sh *sh)
{
	ft_wait_job(job, WUNTRACED | WNOHANG | WCONTINUED, sh);
	if (!(ft_any_running(job) || ft_any_stopped(job)))
	{
		ft_putstr_fd("42sh: fg: job has terminated\n", STDERR_FILENO);
		sh->retval = 1;
	}
	else
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &(job->term));
		tcsetpgrp(STDIN_FILENO, job->pgid);
		if (ft_any_stopped(job))
			kill(-job->pgid, SIGCONT);
		ft_putstr_fd(job->cmdline, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		job->stopped = false;
		sh->retval = ft_manage_job(job, sh);
	}
}

void			builtin_fg(t_42sh *sh)
{
	t_joblist	*job;

	if (sh->pgid)
	{
		ft_putstr_fd("42sh: fg: no job control\n", STDERR_FILENO);
		sh->retval = 1;
	}
	else
	{
		job = NULL;
		if (sh->argv->argv[1] && ft_str_isdigit(sh->argv->argv[1]))
			job = ft_search_job(sh->jobs, ft_atoi(sh->argv->argv[1]));
		else if (!sh->argv->argv[1] || sh->argv->argv[1][0] == '+')
			job = sh->current;
		if (job)
			ft_fg(job, sh);
		else
			ft_no_such_job(sh->argv->argv[1], "fg");
	}
}

void			ft_bg(t_joblist *job, t_42sh *sh)
{
	ft_wait_job(job, WUNTRACED | WNOHANG | WCONTINUED, sh);
	if (!(ft_any_running(job) || ft_any_stopped(job)))
	{
		ft_putstr_fd("42sh: bg: job has terminated\n", STDERR_FILENO);
		sh->retval = 1;
	}
	else
	{
		if (ft_any_stopped(job))
		{
			kill(-job->pgid, SIGCONT);
			ft_put_job_title(job, sh, STDOUT_FILENO);
			ft_putstr_fd(job->cmdline, STDOUT_FILENO);
			ft_putstr_fd(" &\n", STDOUT_FILENO);
			ft_wait_job(job, WUNTRACED | WNOHANG | WCONTINUED, sh);
		}
		else
		{
			ft_putstr_fd("42sh: bg: job ", STDERR_FILENO);
			ft_putnbr_fd(job->num, STDERR_FILENO);
			ft_putstr_fd(" already in background\n", STDERR_FILENO);
		}
	}
}

void			builtin_bg(t_42sh *sh)
{
	t_joblist	*job;

	sh->retval = 0;
	if (sh->pgid)
	{
		ft_putstr_fd("42sh: bg: no job control\n", STDERR_FILENO);
		sh->retval = 1;
	}
	else
	{
		job = NULL;
		if (sh->argv->argv[1] && ft_str_isdigit(sh->argv->argv[1]))
			job = ft_search_job(sh->jobs, ft_atoi(sh->argv->argv[1]));
		else if (!sh->argv->argv[1] || sh->argv->argv[1][0] == '+')
			job = sh->current;
		if (job)
			ft_bg(job, sh);
		else
			ft_no_such_job(sh->argv->argv[1], "bg");
	}
}
