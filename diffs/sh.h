[1mdiff --git a/includes/sh.h b/includes/sh.h[m
[1mindex 50c589d..892765e 100644[m
[1m--- a/includes/sh.h[m
[1m+++ b/includes/sh.h[m
[36m@@ -6,7 +6,7 @@[m
 /*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */[m
 /*                                                +#+#+#+#+#+   +#+           */[m
 /*   Created: 2018/07/29 04:26:44 by jolabour          #+#    #+#             */[m
[31m-/*   Updated: 2019/04/12 08:52:17 by geargenc         ###   ########.fr       */[m
[32m+[m[32m/*   Updated: 2019/04/12 11:53:31 by geargenc         ###   ########.fr       */[m
 /*                                                                            */[m
 /* ************************************************************************** */[m
 [m
[36m@@ -31,6 +31,8 @@[m
 # include "histo.h"[m
 # include "lexer.h"[m
 # include "ast.h"[m
[32m+[m[32m# include "jobs.h"[m
[32m+[m[32m# include "exe.h"[m
 [m
 # define INITIAL_HASHTABLE_SIZE (1U << 9)[m
 # define BUCKET t_bucket[m
[36m@@ -59,8 +61,6 @@[m
 # define SET_FG_RED		"\x1b[38;5;196m"[m
 # define RESET_COLOR	"\x1b[0m"[m
 [m
[31m-# define EOFWHILELOOK "42sh: unexpected EOF while looking for matching `"[m
[31m-[m
 # ifdef MINISHELL[m
 #  define PROG_NAME "minishell"[m
 # elif defined _21SH[m
[36m@@ -100,37 +100,6 @@[m [mtypedef struct				s_list_ari[m
 	char					*name;[m
 }							t_list_ari;[m
 [m
[31m-typedef struct				s_proclist[m
[31m-{[m
[31m-	pid_t					pid;[m
[31m-	t_node					*command;[m
[31m-	char					*cmdline;[m
[31m-	int						status;[m
[31m-	bool					complete;[m
[31m-	char					*path;[m
[31m-	char					**args;[m
[31m-	struct s_proclist		*next;[m
[31m-}							t_proclist;[m
[31m-[m
[31m-typedef struct				s_joblist[m
[31m-{[m
[31m-	pid_t					pgid;[m
[31m-	t_proclist				*process;[m
[31m-	char					*cmdline;[m
[31m-	int						num;[m
[31m-	bool					stopped;[m
[31m-	struct termios			term;[m
[31m-	struct s_joblist		*next;[m
[31m-}							t_joblist;[m
[31m-[m
[31m-typedef struct				s_tmpfd[m
[31m-{[m
[31m-	int						initial;[m
[31m-	int						tmp;[m
[31m-	int						cloexec;[m
[31m-	struct s_tmpfd			*next;[m
[31m-}							t_tmpfd;[m
[31m-[m
 typedef enum				e_errno_val[m
 {[m
 	_ENOMEM = 1,[m
[36m@@ -295,12 +264,6 @@[m [mtypedef struct				s_42sh[m
 	bool					print_pwd;[m
 }							t_42sh;[m
 [m
[31m-typedef struct				s_bttab[m
[31m-{[m
[31m-	char					*name;[m
[31m-	void					(*f)(t_42sh *);[m
[31m-}							t_bttab;[m
[31m-[m
 typedef struct				s_spparam[m
 {[m
 	char					c;[m
[36m@@ -347,13 +310,23 @@[m [mtypedef struct				s_class[m
 }							t_class;[m
 [m
 void						ft_init(t_42sh *shell);[m
[31m-char						*ft_strjoinfree(char *s1, char *s2,[m
[31m-		unsigned int which);[m
 [m
 /*[m
 **							<--UTILS-->[m
 */[m
 [m
[32m+[m[32m/*[m
[32m+[m[32m**-->						struct[m
[32m+[m[32m*/[m
[32m+[m
[32m+[m[32mtypedef struct				s_opt[m
[32m+[m[32m{[m
[32m+[m	[32mchar					**argv;[m
[32m+[m	[32mchar					**after_opts;[m
[32m+[m	[32mbool					available[256];[m
[32m+[m	[32mbool					set[256];[m
[32m+[m[32m}							t_opt;[m
[32m+[m
 /*[m
 **-->						ft_continue_line.c[m
 */[m
[36m@@ -364,37 +337,22 @@[m [mint							ft_continue_line(t_42sh *shell, char **line,[m
 		char *matching);[m
 [m
 /*[m
[31m-**							exe[m
[32m+[m[32m**-->						tools.c[m
 */[m
 [m
[31m-int							check_builtin(t_42sh *sh);[m
[31m-void						free_tab(char **str);[m
[31m-void						ft_reset_signals(void);[m
[31m-void						ft_launch_job(t_joblist *job, t_42sh *shell);[m
[31m-int							ft_manage_job(t_joblist *job, t_42sh *shell);[m
[31m-int							ft_wait_job(t_joblist *job, int options,[m
[31m-		t_42sh *shell);[m
[31m-int							ft_exe_pipe(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_and(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_semi(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_great(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_less(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_rpar(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_and_if(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_or_if(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_dgreat(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_lessand(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_lessanddash(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_greatand(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_greatanddash(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_lessgreat(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_dless(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_rbrace(t_node *current, t_42sh *shell);[m
[31m-int							ft_exe_command(t_node *current, t_42sh *shell);[m
[31m-int							ft_pipe_exit(int pipefd[2]);[m
[31m-pid_t						ft_fork_exit(void);[m
[31m-int							ft_dup_exit(int fd);[m
[31m-int							ft_dup2_exit(int fd1, int fd2);[m
[32m+[m[32mchar						*ft_strjoinfree(char *s1, char *s2,[m
[32m+[m		[32munsigned int which);[m
[32m+[m[32mint							ft_str_isdigit(char *str);[m
[32m+[m[32mint							ft_str_isquote(char *str);[m
[32m+[m[32mint							ft_chars_in_int(int nbr);[m
[32m+[m
[32m+[m[32m/*[m
[32m+[m[32m**-->						ft_get_opts.c[m
[32m+[m[32m*/[m
[32m+[m
[32m+[m[32mvoid						ft_init_opts(t_opt *opt, char *available);[m
[32m+[m[32mint							ft_bad_opt(char *head, char opt);[m
[32m+[m[32mint							ft_get_opts(t_opt *opt, char **argv, char *error);[m
 [m
 /*[m
 **							expanse[m
[36m@@ -441,48 +399,15 @@[m [mchar						*ft_expanse_word(char *word, t_42sh *shell);[m
 char						*ft_simple_expanse(char *word, t_42sh *shell);[m
 void						ft_rmquotes_word(char *word);[m
 [m
[31m-/*[m
[31m-**							cmdline_command[m
[31m-*/[m
[31m-[m
[31m-char						*ft_cmdline_sep(t_node *command);[m
[31m-char						*ft_cmdline_redir(t_node *command);[m
[31m-char						*ft_cmdline_par(t_node *command);[m
[31m-char						*ft_cmdline_redir_and(t_node *command);[m
[31m-char						*ft_cmdline_redir_close(t_node *command);[m
[31m-char						*ft_cmdline_brace(t_node *command);[m
[31m-char						*ft_cmdline_command(t_node *command);[m
[31m-[m
[31m-/*[m
[31m-**							jobs[m
[31m-*/[m
[31m-[m
[31m-int							ft_any_stopped(t_joblist *job);[m
[31m-int							ft_any_running(t_joblist *job);[m
[31m-void						ft_report_job_def(t_joblist *job, t_42sh *sh,[m
[31m-		int fd);[m
[31m-void						ft_check_jobs(t_42sh *shell);[m
[31m-void						builtin_jobs(t_42sh *sh);[m
[31m-void						ft_remove_job(t_joblist *job, t_42sh *shell);[m
[31m-int							ft_manage_job(t_joblist *job, t_42sh *shell);[m
[31m-void						builtin_fg(t_42sh *sh);[m
[31m-void						builtin_bg(t_42sh *sh);[m
[31m-[m
 /*[m
 **							globals[m
 */[m
 [m
[31m-extern int					(*g_exetab[])(t_node *current, t_42sh *shell);[m
[31m-extern t_bttab				g_bttab[];[m
 extern t_spparam			g_spparamtab[];[m
 extern int					(*g_txttab[])(char *word, size_t *index,[m
 		t_txtlist **current, bool *dquote);[m
 extern char					*g_txtstr[];[m
 extern int					(*g_exptab[])(t_txtlist *txt, t_42sh *shell);[m
[31m-extern char					*g_sigtab[];[m
[31m-extern char					*g_sigabrevtab[];[m
[31m-extern char					*(*g_cmdlinetab[])(t_node *command);[m
[31m-extern int					g_intr;[m
 extern t_class				g_classestab[];[m
 typedef t_matchlist			*(*t_getmatch)(char *);[m
 extern t_getmatch			g_getmatchtab[];[m
[36m@@ -637,6 +562,7 @@[m [mchar						**list_to_tab(t_env *env, char **copy_env);[m
 t_env						*create_node(char *str);[m
 void						lst_push(t_env **head, t_env *new);[m
 t_env						*set_list(char **env);[m
[32m+[m[32mvoid						free_tab(char **str);[m
 [m
 /*[m
 **							getenv[m
