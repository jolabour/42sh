/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:33:34 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/26 05:53:05 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBS_H

# define JOBS_H

# include "sh.h"

typedef struct s_42sh		t_42sh;
typedef struct s_opt		t_opt;

/*
**							struct
*/

typedef struct				s_proclist
{
	pid_t					pid;
	t_node					*command;
	char					*cmdline;
	int						status;
	bool					complete;
	char					*path;
	char					**args;
	struct s_proclist		*next;
}							t_proclist;

typedef struct				s_joblist
{
	pid_t					pgid;
	t_proclist				*process;
	char					*cmdline;
	int						num;
	bool					stopped;
	struct termios			term;
	struct s_joblist		*next;
}							t_joblist;

/*
**							globals
*/

extern char					*g_sigtab[];
extern char					*g_sigabrevtab[];
extern char					*(*g_cmdlinetab[])(t_node *command);
extern int					g_intr;

/*
**							ft_jobs_any.c
*/

int							ft_any_stopped(t_joblist *job);
int							ft_any_running(t_joblist *job);
int							ft_any_interrupted(t_joblist *job);

/*
**							ft_jobs_check.c
*/

void						ft_check_job(t_joblist *job, t_42sh *shell);
void						ft_check_jobs(t_42sh *shell);

/*
**							ft_jobs_cmdlineX.c (1 <= X <= 2)
*/

char						*ft_cmdline_sep(t_node *command);
char						*ft_cmdline_redir(t_node *command);
char						*ft_cmdline_par(t_node *command);
char						*ft_cmdline_redir_and(t_node *command);
char						*ft_cmdline_redir_close(t_node *command);
char						*ft_cmdline_brace(t_node *command);
char						*ft_cmdline_assigns(t_node *command);
char						*ft_cmdline_words(t_node *command);
char						*ft_cmdline_command(t_node *command);

/*
**							ft_jobs_error.c
*/

void						ft_no_such_job(char *job, char *builtin);
void						ft_put_job_title(t_joblist *job, t_42sh *sh,
		int fd);

/*
**							ft_jobs_get.c
*/

t_proclist					*ft_get_pipeline(t_node *current);
int							ft_get_job_number(t_joblist *jobs);
void						ft_push_job_back(t_joblist *job, t_42sh *shell);
t_joblist					*ft_get_job(t_node *current, t_42sh *shell);

/*
**							ft_jobs_launch.c
*/

void						ft_launch_process(t_proclist *proc, t_42sh *shell,
		int pipefd[3], pid_t pgid);
void						ft_launch_job(t_joblist *job, t_42sh *shell);

/*
**							ft_manage_jobs.c
*/

int							ft_wait_job(t_joblist *job, int options,
		t_42sh *shell);
int							ft_get_retval(int status);
void						ft_manage_status(t_joblist *job, t_42sh *shell);
int							ft_manage_job(t_joblist *job, t_42sh *shell);

/*
**							ft_jobs_remove.c
*/

t_joblist					*ft_get_last_job(t_joblist *jobs);
void						ft_remove_proc(t_proclist *proc);
void						ft_remove_job(t_joblist *job, t_42sh *shell);

/*
**							ft_jobs_report.c
*/

void						ft_report_job_long(t_joblist *job, t_42sh *sh,
		int fd);
void						ft_report_job_pgid(t_joblist *job, t_42sh *sh,
		int fd);
void						ft_report_job_def(t_joblist *job, t_42sh *sh,
		int fd);
void						ft_report_job(t_opt *opt, t_joblist *job,
		t_42sh *sh);
void						ft_report_all_jobs(t_opt *opt, t_42sh *sh);

/*
**							ft_jobs_signals.c
*/

void						ft_reset_signals(void);
void						ft_init_signals(void);
void						ft_handler(int sig);

/*
**							ft_jobs_status.c
*/

int							ft_exited(t_proclist *proc, int fd);
int							ft_signaled(int status, int fd);
int							ft_stopped_long(int status, int fd);
int							ft_stopped(int status, int fd);
int							ft_running(int status, int fd);

/*
**							ft_jobs_tools.c
*/

t_joblist					*ft_search_job(t_joblist *list, int num);
void						ft_print_bg(t_joblist *job, t_42sh *shell);

/*
**							builtins
*/

void						builtin_jobs(t_42sh *sh);
void						builtin_fg(t_42sh *sh);
void						builtin_bg(t_42sh *sh);

#endif
