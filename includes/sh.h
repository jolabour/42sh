/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 04:26:44 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/07 10:17:07 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <term.h>
# include <curses.h>
# include <pwd.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft.h"
# include "histo.h"

# define INITIAL_HASHTABLE_SIZE (1U << 9)
# define BUCKET t_bucket
# define BUCKET_CONTENT t_bucket_content
# define OPTION_TEST 15
# define NB_INPUT_SELECT 8
# define NB_INPUT 17
# define RIGHT_KEY 4414235
# define LEFT_KEY 4479771
# define HOME 4741915
# define END 4610843
# define CTRL_C 3
# define CTRL_D 4
# define CTRL_R 18
# define DEL 127
# define UP_KEY 4283163
# define DOWN_KEY 4348699
# define TAB 9
# define OPT_B 11241698
# define OPT_F 37574
# define OPT_C 42947
# define OPT_X 8948194
# define OPT_V 10127586
# define OPT_UP 1096489755
# define OPT_DOWN 1113266971
# define SET_FG_RED		"\x1b[38;5;196m"
# define RESET_COLOR	"\x1b[0m"

# define EOFWHILELOOK "42sh: unexpected EOF while looking for matching `"

# ifdef MINISHELL
#  define PROG_NAME "minishell"
# elif defined _21SH
#  define PROG_NAME "21sh"
# else
#  define PROG_NAME "21sh"
# endif

typedef enum				e_tok
{
	NONE = 0,
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE,
	IO_NUMBER,
	OPP,
	PIPE,
	AND,
	SEMI,
	GREAT,
	LESS,
	LPAR,
	RPAR,
	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	LESSAND,
	LESSANDDASH,
	GREATAND,
	GREATANDDASH,
	LESSGREAT,
	DLESSDASH,
	CLOBBER,
	LBRACE,
	RBRACE,
	COMMAND
}							t_tok;

typedef struct				s_toktab
{
	char					*str;
	t_tok					token;
	bool					alias_recognition;
	bool					redir_op;
}							t_toktab;

typedef struct				s_toklist
{
	t_tok					token;
	size_t					start;
	size_t					len;
	struct s_toklist		*next;
}							t_toklist;

typedef struct				s_node
{
	t_tok					token;
	char					*data;
	struct s_node			*left;
	struct s_node			*right;
	struct s_node			*parent;
	struct s_node			*redir;
}							t_node;

typedef enum				e_txttype
{
	TXT_NONE = 0,
	TEXT,
	TILDE,
	VAR,
	BRACE_VAR,
	CMD_SUB,
	CMD_SUB_BQUOTE,
	ARTH_EXPR
}							t_txttype;

typedef struct				s_txtlist
{
	t_txttype				token;
	char					*data;
	size_t					start;
	size_t					len;
	int						dquote;
	struct s_txtlist		*next;
}							t_txtlist;

typedef struct				s_list_ari
{
	struct s_list_ari		*next;
	int						nbr;
	int						opt;
	char					*var;
	char					*name;
}							t_list_ari;

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

typedef struct				s_tmpfd
{
	int						initial;
	int						tmp;
	int						cloexec;
	struct s_tmpfd			*next;
}							t_tmpfd;

typedef enum				e_errno_val
{
	_ENOMEM = 1,
	_ENAMETOOLONG,
	_ENOENV,
	_ENAMEENV,
	_ENOHOME,
	_ENOUSER,
	_ENOVAR,
	_ENOCMD,
	_ELOOP,
	_ENOTDIR,
	_EINVAL,
	_ENOENT,
	_ENOX,
	_ERRNO_VALUES
}							t_errno;

static t_errno				g_errno;
static const char			*g_errors[_ERRNO_VALUES];

typedef struct				s_env
{
	char					*str;
	struct s_env			*next;
}							t_env;

typedef struct				s_bucket_content
{
	struct s_bucket_content	*next;
	char					*name;
	char					*path;
	size_t					pathlen;
}							t_bucket_content;

typedef struct				s_bucket
{
	BUCKET_CONTENT			*first;
	uint8_t					length;
}							t_bucket;

typedef struct				s_ht
{
	BUCKET					buckets[INITIAL_HASHTABLE_SIZE];
	uint16_t				used;
	uint16_t				capacity;
}							t_ht;

typedef struct termios		t_term;
typedef struct termios		t_reset;

typedef struct				s_stdin
{
	int						line_pos;
	int						len_line;
	char					*str_to_paste;
	int						nb_line;
	int						start_und;
	int						end_und;
	int						ctrlc;
	int						cursor_pos;
	int						save_pos;
	int						size_of_input;
	char					*input;
}							t_stdin;

typedef struct				s_alias
{
	char					*to_sub;
	char					*sub;
	struct s_alias			*prev;
	struct s_alias			*next;
}							t_alias;

typedef struct				s_alias_mark
{
	t_alias					*begin;
	t_alias					*last;
	int						size;
}							t_alias_mark;

typedef struct				s_var
{
	char					*to_sub;
	char					*sub;
	struct s_var			*next;
}							t_var;

typedef struct				s_var_mark
{
	t_var					*begin;
	int						size;
}							t_var_mark;

typedef struct				s_argv
{
	char					**argv;
	int						pos_str;
	int						cur_str;
	int						error_code;
	int						size;
}							t_argv;

typedef struct				s_42sh
{
	char					**tokens;
	char					**builtin;
	char					**args;
	t_argv					*argv;
	char					*valide_path;
	int						winsize;
	int						prompt_len;
	char					*prompt;
	char					*pwd;
	char					**bin_dirs;
	char					**copy_env;
	char					*path_history;
	int						token_nbr;
	bool					need_get_line;
	t_stdin					*stdin;
	t_history_mark			*history_mark;
	char					*line_to_replace;
	int						substitute_on;
	t_env					*env;
	t_term					term;
	t_reset					reset_term;
	t_alias_mark			*alias;
	t_ht					hashtable;
	t_var_mark				*var;
	t_list_ari				*ari;
	char					*arg_r;
	pid_t					pgid;
	int						forked;
	t_joblist				*jobs;
	t_joblist				*current;
	pid_t					pid;
	pid_t					last_bg;
	int						retval;
	int						foreground;
	t_tmpfd					*tmp_fds;
	bool					stopexe;
	bool					buffer_mode;
	char					*buffer;
}							t_42sh;

typedef struct				s_lex
{
	char					*input;
	size_t					index;
	t_toklist				*begin;
	t_toklist				*current;
	bool					alias_recognition;
	bool					redir_op;
	size_t					ignore_alias;
}							t_lex;

typedef struct				s_tokcond
{
	int						(*cond)(t_lex *, t_42sh *);
	int						dquote_mode;
	int						sub_mode;
}							t_tokcond;

typedef struct				s_ast
{
	t_node					*begin;
	t_node					*current;
	t_node					*list;
}							t_ast;

typedef struct				s_bttab
{
	char					*name;
	void					(*f)(t_42sh *);
}							t_bttab;

typedef struct				s_spparam
{
	char					c;
	char					*(*f)(t_42sh *);
}							t_spparam;

void						ft_init(t_42sh *shell);
char						*ft_strjoinfree(char *s1, char *s2,
		unsigned int which);

/*
**							lexer
*/

int							ft_lex_operator(t_lex *lex, t_42sh *shell);
int							ft_lex_notoperator(t_lex *lex, t_42sh *shell);
int							ft_lex_newline(t_lex *lex, t_42sh *shell);
int							ft_lex_backslash(t_lex *lex, t_42sh *shell);
int							ft_lex_quote(t_lex *lex, t_42sh *shell);
int							ft_lex_dquote(t_lex *lex, t_42sh *shell);
int							ft_lex_dollar(t_lex *lex, t_42sh *shell);
int							ft_lex_bquote(t_lex *lex, t_42sh *shell);
int							ft_lex_ionumber(t_lex *lex, t_42sh *shell);
int							ft_lex_newoperator(t_lex *lex, t_42sh *shell);
int							ft_lex_blank(t_lex *lex, t_42sh *shell);
int							ft_lex_sharp(t_lex *lex, t_42sh *shell);
int							ft_lex_word(t_lex *lex, t_42sh *shell);
int							ft_lex_newword(t_lex *lex, t_42sh *shell);
int							ft_lexer(t_lex *lex, t_42sh *shell);
void						ft_print_toklist(char *input, t_toklist *list);
int							ft_continue_line(t_42sh *shell, char **line,
		char *matching);

/*
**							ast
*/

int							ft_ast_word(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_newline(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_io_number(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_badtoken(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_pipe(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_separator(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_redir(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_lpar(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_rpar(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_and_or(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_heredoc(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_closefd(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_lbrace(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_rbrace(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
t_node						*ft_toklist_to_node(char *input, t_toklist *list);
void						ft_ast_free(t_node *ast);
int							ft_build_ast(t_ast *ast, t_42sh *shell);

/*
**							exe
*/

int							check_builtin(t_42sh *sh);
void						free_tab(char **str);
void						ft_launch_job(t_joblist *job, t_42sh *shell);
int							ft_manage_job(t_joblist *job, t_42sh *shell);
int							ft_wait_job(t_joblist *job, int options,
		t_42sh *shell);
int							ft_exe_badtoken(t_node *current, t_42sh *shell);
int							ft_exe_pipe(t_node *current, t_42sh *shell);
int							ft_exe_and(t_node *current, t_42sh *shell);
int							ft_exe_semi(t_node *current, t_42sh *shell);
int							ft_exe_great(t_node *current, t_42sh *shell);
int							ft_exe_less(t_node *current, t_42sh *shell);
int							ft_exe_rpar(t_node *current, t_42sh *shell);
int							ft_exe_and_if(t_node *current, t_42sh *shell);
int							ft_exe_or_if(t_node *current, t_42sh *shell);
int							ft_exe_dgreat(t_node *current, t_42sh *shell);
int							ft_exe_lessand(t_node *current, t_42sh *shell);
int							ft_exe_lessanddash(t_node *current, t_42sh *shell);
int							ft_exe_greatand(t_node *current, t_42sh *shell);
int							ft_exe_greatanddash(t_node *current, t_42sh *shell);
int							ft_exe_lessgreat(t_node *current, t_42sh *shell);
int							ft_exe_dless(t_node *current, t_42sh *shell);
int							ft_exe_rbrace(t_node *current, t_42sh *shell);
int							ft_exe_command(t_node *current, t_42sh *shell);
int							ft_pipe_exit(int pipefd[2]);
pid_t						ft_fork_exit(void);
int							ft_dup_exit(int fd);
int							ft_dup2_exit(int fd1, int fd2);

/*
**							expanse
*/

typedef char *(*t_param)(t_42sh *);

t_param						ft_get_spparam(char c);
int							ft_parse_tilde(char *word, size_t *index,
		t_txtlist **current, int *dquote);
int							ft_parse_var(char *word, size_t *index,
		t_txtlist **current, int *dquote);
int							ft_parse_bquote(char *word, size_t *index,
		t_txtlist **current, int *dquote);
int							ft_parse_backslash(char *word, size_t *index,
		t_txtlist **current, int *dquote);
int							ft_parse_quote(char *word, size_t *index,
		t_txtlist **current, int *dquote);
int							ft_parse_text(char *word, size_t *index,
		t_txtlist **current, int *dquote);
char						*ft_spparam_dollar(t_42sh *shell);
char						*ft_spparam_qmark(t_42sh *shell);
char						*ft_spparam_bang(t_42sh *shell);
char						*ft_spparam_zero(t_42sh *shell);
int							ft_exp_text(t_txtlist *txt, t_42sh *shell);
int							ft_exp_tilde(t_txtlist *txt, t_42sh *shell);
int							ft_exp_var(t_txtlist *txt, t_42sh *shell);
int							ft_exp_brace(t_txtlist *txt, t_42sh *shell);
int							ft_exp_sub(t_txtlist *txt, t_42sh *shell);
int							ft_exp_bquote(t_txtlist *txt, t_42sh *shell);
int							ft_exp_expr(t_txtlist *txt, t_42sh *shell);
char						*ft_simple_expanse(char *word, t_42sh *shell);
void						ft_rmquotes_word(char *word);

/*
**							cmdline_command
*/

char						*ft_cmdline_badtoken(t_node *command);
char						*ft_cmdline_sep(t_node *command);
char						*ft_cmdline_redir(t_node *command);
char						*ft_cmdline_par(t_node *command);
char						*ft_cmdline_redir_and(t_node *command);
char						*ft_cmdline_redir_close(t_node *command);
char						*ft_cmdline_brace(t_node *command);
char						*ft_cmdline_command(t_node *command);

/*
**						jobs
*/

int							ft_any_stopped(t_joblist *job);
int							ft_any_running(t_joblist *job);
void						ft_report_job_def(t_joblist *job, t_42sh *sh,
		int fd);
void						ft_check_jobs(t_42sh *shell);
void						builtin_jobs(t_42sh *sh);
void						ft_remove_job(t_joblist *job, t_42sh *shell);
int							ft_manage_job(t_joblist *job, t_42sh *shell);
void						builtin_fg(t_42sh *sh);
void						builtin_bg(t_42sh *sh);

/*
**						globals
*/

extern char					*g_tokstr[];
extern t_toktab				g_toktab[];
extern t_tokcond			g_tokcond[];
extern int					(*g_asttab[])(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
extern int					(*g_exetab[])(t_node *current, t_42sh *shell);
extern t_bttab				g_bttab[];
extern t_spparam			g_spparamtab[];
extern int					(*g_txttab[])(char *word, size_t *index,
		t_txtlist **current, int *dquote);
extern char					*g_txtstr[];
extern int					(*g_exptab[])(t_txtlist *txt, t_42sh *shell);
extern char					*g_sigtab[];
extern char					*g_sigabrevtab[];
extern char					*(*g_cmdlinetab[])(t_node *command);
extern int					g_intr;

typedef void				(*t_ak)(t_42sh *sh);
typedef void				(*t_test_other)(t_42sh *sh, int *pos);
typedef void				(*t_test)(t_42sh *sh, struct stat info);

/*
**						select_mode
*/

void						select_mode(t_42sh *sh);
void						clean_print_select(t_42sh *sh);

/*
**							keymap_select
*/

int							check_input_select(t_42sh *sh, long buf);

/*
**							move_select_mode
*/

void						move_to_right_select(t_42sh *sh);
void						move_to_left_select(t_42sh *sh);

/*
**							exit_select_mode
*/

void						exit_select_mode(t_42sh *sh, int pos);

/*
**							action_select_mode
*/

void						copy_select(t_42sh *sh);
void						del_select(t_42sh *sh);
void						cut_select(t_42sh *sh);

/*
**							stdin
*/

int							get_line(t_42sh *sh);
int							get_winsize(void);
void						ft_paste(t_42sh *sh);
void						clean_print(t_42sh *sh);
int							get_curent_line(t_42sh *sh);
void						up_input(t_42sh *sh);

/*
**							check_input
*/

int							check_input(t_42sh *sh, long buf);

/*
**							control_action
*/

void						ctrlc_action(t_42sh *sh);
void						ctrld_action(t_42sh *sh);
void						paste(t_42sh *sh);

/*
**							insert_mode
*/

void						insert_mode_on(void);
void						insert_mode_off(void);

/*
**							manip_input
*/

void						add_char(long input, t_42sh *sh);
void						delete_char(t_42sh *sh);
void						delete_input(t_42sh *sh);
void						delete_input_buf(t_42sh *sh);
void						delete_cut(t_42sh *sh);
void						delete_after_cursor(t_42sh *sh);
void						delete(void);

/*
**							process
*/

char						*check_access(t_42sh *sh, int pos);
void						process(t_42sh *sh);

/*
**							move_arrows
*/

int							putchar_custom(int c);
void						move_to_right(t_42sh *sh);
void						move_to_left(t_42sh *sh);
void						move_to_start(t_42sh *sh);
void						move_to_end(t_42sh *sh);

/*
**							move_word
*/

void						move_to_begin_word(t_42sh *sh);
void						move_to_end_word(t_42sh *sh);

/*
**							move_line
*/

void						move_down(t_42sh *sh);
void						move_up(t_42sh *sh);

/*
**							process
*/

void						process(t_42sh *sh);

/*
**							prompt
*/

void						prompt(t_env *list, t_42sh *sh);

/*
**							hash_table
*/

BUCKET_CONTENT				*ht_lookup(const char *s, t_ht *ht);
BUCKET_CONTENT				*ht_insert(const char *path, const char *name,
		t_ht *ht);
void						ht_delete(const char *name, t_ht *ht);
void						init_hashtable(t_42sh *sh);
void						print_hashtable(t_ht ht);
void						get_fork(t_42sh *sh);
void						builtin_hash(t_42sh *sh);

/*
**							list
*/

int							len_list(t_env *env);
char						**list_to_tab(t_env *env, char **copy_env);
t_env						*create_node(char *str);
void						lst_push(t_env **head, t_env *new);
t_env						*set_list(char **env);

/*
**							getenv
*/

char						*ft_getenv(t_env *list, const char *name,
		size_t len);

/*
**							init_shell
*/

void						get_term(t_42sh *sh);
void						init_shell(t_42sh *sh, char **env);
int							get_line(t_42sh *sh);
void						reset_term(t_42sh *sh);

/*
**							errno
*/

void						init_error_tab(void);
void						print_error(int code, bool is_fatal);
void						print_error_and_exit(int error_code);
void						print_error_first(int error_code);
int							ft_set_errno(int n);

/*
**							Utils
*/

char						*ft_joinpath(const char *path, const char *name);

void						print_env_array(char **env);
int							check_is_builtin(t_42sh *sh, char *str);

/*
**							history
*/

int							substitute_history(t_42sh *sh, int *i);
char						*search_history_begin(t_42sh *sh, int nb);
char						*search_history_last(t_42sh *sh, int nb);
int							get_nb_history(t_42sh *sh, int pos, int *nb_del);
char						*search_history_char(t_42sh *sh, char **to_find);
char						*search_str_input(t_42sh *sh, int start,
		int *nb_del);
void						up_history(t_42sh *sh);
void						parser(t_42sh *sh);

/*
**							Options
*/

void						history_p(t_42sh *sh);
void						clean_history(char *path);
void						print_history_n(char *path);
void						print_history_r(char *path);
void						init_history(t_42sh *sh, char *line);
void						add_history(t_42sh *sh, char *line, char *path);
void						print_history(t_history_mark *history_mark);
void						del_history(t_history_mark *history);
void						add_to_list(t_42sh *sh, char *line);
void						up_histo(t_42sh *sh);
void						down_histo(t_42sh *sh);
char						*check_substitute(t_42sh *sh, char *str,
		int *error);
void						modify_last_history(t_42sh *sh);
void						ctrlr_action(t_42sh *sh);
int							is_in_str(char *to_find, char *search,
		int len_check);
void						get_new_line_ctrlr(t_42sh *sh, char *dup);
char						*get_line_ctrlr(t_42sh *sh, char *arg, char *dup);
void						place_curs_ctrlr(t_42sh *sh, char *arg, char *dup);
void						print_prompt_search(t_42sh *sh, int choice,
		char *to_print_out, int len_del);
void						place_curs_ctrlr_exit(t_42sh *sh, char *arg,
		char *dup);
void						back_in_history(t_42sh *sh, char *dup, char *arg);

/*
**						test
*/

void						builtin_test(t_42sh *sh);
void						test_b(t_42sh *sh, struct stat info);
void						test_c(t_42sh *sh, struct stat info);
void						test_d(t_42sh *sh, struct stat info);
void						test_e(t_42sh *sh, struct stat info);
void						test_f(t_42sh *sh, struct stat info);
void						test_g(t_42sh *sh, struct stat info);
void						test_l(t_42sh *sh, struct stat info);
void						test_p(t_42sh *sh, struct stat info);
void						test_r(t_42sh *sh, struct stat info);
void						test_su(t_42sh *sh, struct stat info);
void						test_s(t_42sh *sh, struct stat info);
void						test_u(t_42sh *sh, struct stat info);
void						test_w(t_42sh *sh, struct stat info);
void						test_x(t_42sh *sh, struct stat info);
void						test_z(t_42sh *sh, struct stat info);
void						test_equal(t_42sh *sh, int *pos);
void						test_diff(t_42sh *sh, int *pos);
void						test_eq(t_42sh *sh, int *pos);
void						test_ne(t_42sh *sh, int *pos);
void						test_ge(t_42sh *sh, int *pos);
void						test_lt(t_42sh *sh, int *pos);
void						test_le(t_42sh *sh, int *pos);
int							execute_other_opt(t_42sh *sh, char *str, int *j);

/*
**							echo
*/

void						builtin_echo(t_42sh *sh);

/*
**							alias
*/

void						builtin_alias(t_42sh *sh);
void						builtin_unalias(t_42sh *sh);

/*
**							fc
*/

void						builtin_fc(t_42sh *sh);

/*
**							type
*/

void						builtin_type(t_42sh *sh);

/*
**							parser
*/

int							check_substitute_history(t_42sh *sh);
void						get_substitute(t_42sh *sh, int i,
		char *substitute, int nb_del);
void						show_suggest(t_42sh *sh);
int							parse_test(t_42sh *sh);
void						builtin_set(t_42sh *sh);
void						builtin_unset(t_42sh *sh);
void						reset_hashtable(t_ht *ht);
int							check_equal(char *str);
void						builtin_export(t_42sh *sh);
int							search_var(t_var_mark *var_mark, t_var **var,
		char *str);
int							check_env(t_env **env, char **split);
void						list_del(t_env **env, t_env *to_del, t_env *prev);
char						*substitute_alias(char *name, t_42sh *sh);
void						*ft_malloc_exit(size_t size);
char						**ft_command_to_args(t_node *current,
		t_42sh *shell);
char						*get_var(t_42sh *sh, char *str);
void						list_alias(t_42sh *sh);
t_alias						*new_alias(char **line);
void						add_to_list_alias(t_42sh *sh, char **split);
void						lst_del(t_alias **alias, t_alias *to_del,
		t_alias *prev);
int							check_alias(t_alias_mark **alias, char **split);
void						print_export(t_42sh *sh);
void						print_type_alias(t_42sh *sh, int i, char *str);
void						print_type_builtin(t_42sh *sh, int i);
void						print_type_error(t_42sh *sh, int i);
void						print_type_binary(t_42sh *sh, int i, char *str);
void						print_type_hash(t_42sh *sh, int i, char *str);
void						lst_del_var(t_var **var, t_var *to_del,
		t_var *prev);
int							ft_str_isdigit(char *str);
void						builtin_exit(t_42sh *sh);
int							check_valid_var(char *str);
int							check_var(t_var_mark **var, char **split);

/*
**							ft_erase_space.c
*/

char						*ft_erase_space(char *str);

/*
**							ft_true_op.c
*/

char						*ft_true_op(char *str, int size);

/*
**							ft_logic_op.c
*/

char						*ft_logic_op(char *str, int size);

/*
**							ft_math_op.c
*/

char						*ft_math_op(char *str, int n);
int							ft_count_prev_num(char *str, int m);
int							ft_count_next_num(char *str);

/*
**							ft_itoa_exp_ari.c
*/

void						ft_itoa_exp_ari(char *str, int nbr, int n);

/*
**							ft_exp_ari_error.c
*/

void						ft_exp_ari_error(char *str);

/*
**							ft_check_exp_ari.c
*/

int							ft_check_exp_ari(char *str);

/*
**							ft_check_var.c
*/

char						*ft_check_var(char *str, t_list_ari *list_var);
char						*ft_exp_ari(char *str, int len);

void						check_local_variable(t_42sh *sh, char *str);

#endif
