/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 04:26:44 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/20 02:42:01 by achavy           ###   ########.fr       */
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
# include <dirent.h>
# include "libft.h"
# include "histo.h"
# include "lexer.h"
# include "ast.h"
# include "jobs.h"
# include "exe.h"
# include "exp.h"

# define INITIAL_HASHTABLE_SIZE (1U << 9)
# define BUCKET t_bucket
# define BUCKET_CONTENT t_bucket_content
# define OPTION_TEST 15
# define NB_INPUT_SELECT 8
# define NB_INPUT 16
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

# ifdef MINISHELL
#  define PROG_NAME "minishell"
# elif defined _21SH
#  define PROG_NAME "21sh"
# else
#  define PROG_NAME "21sh"
# endif

typedef struct				s_list_ari
{
	struct s_list_ari		*next;
	int						nbr;
	int						opt;
	char					*var;
	char					*name;
}							t_list_ari;

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

typedef struct				s_path
{
	char					*str;
	struct s_path			*next;
}							t_path;

typedef struct				s_path_mark
{
	t_path					*begin;
	int						size;
}							t_path_mark;

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
	int						ctrld;
	char					**tokens;
	char					**builtin;
	char					**args;
	t_argv					*argv;
	char					*valide_path;
	int						winsize;
	int						prompt_len;
	char					*prompt;
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
	t_path_mark				*path;
	char					*path_cd;
	int						exit_lock;
	char					**cd_path;
	int						cd_err;
	char					*pwd;
	bool					print_pwd;
}							t_42sh;

void						ft_init(t_42sh *shell);

/*
**							<--UTILS-->
*/

/*
**-->						struct
*/

typedef struct				s_opt
{
	char					**argv;
	char					**after_opts;
	bool					available[256];
	bool					set[256];
}							t_opt;

/*
**-->						ft_continue_line.c
*/

int							ft_continue_line_buffer(t_42sh *shell, char **line);
int							ft_continue_line_stdin(t_42sh *shell, char **line);
int							ft_continue_line(t_42sh *shell, char **line,
		char *matching);

/*
**-->						tools.c
*/

char						*ft_strjoinfree(char *s1, char *s2,
		unsigned int which);
int							ft_str_isdigit(char *str);
int							ft_str_isquote(char *str);
int							ft_chars_in_int(int nbr);
char						*ft_strrev(char *str);

/*
**-->						ft_get_opts.c
*/

void						ft_init_opts(t_opt *opt, char *available);
int							ft_bad_opt(char *head, char opt);
int							ft_get_opts(t_opt *opt, char **argv, char *error);

/*
**							expanse
*/

typedef char *(*t_param)(t_42sh *);

t_param						ft_get_spparam(char c);
int							ft_parse_tilde(char *word, size_t *index,
		t_txtlist **current, bool *dquote);
int							ft_parse_var(char *word, size_t *index,
		t_txtlist **current, bool *dquote);
int							ft_parse_bquote(char *word, size_t *index,
		t_txtlist **current, bool *dquote);
int							ft_parse_backslash(char *word, size_t *index,
		t_txtlist **current, bool *dquote);
int							ft_parse_quote(char *word, size_t *index,
		t_txtlist **current, bool *dquote);
int							ft_parse_text(char *word, size_t *index,
		t_txtlist **current, bool *dquote);
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
t_matchlist					*ft_getmatch_wcard(char *word);
t_matchlist					*ft_getmatch_qmark(char *word);
t_matchlist					*ft_getmatch_hook(char *word);
t_matchlist					*ft_getmatch_text(char *word);
t_matchlist					*ft_getmatch_list(char *word);
bool						ft_match_end(char *str, t_matchlist *match);
bool						ft_match_text(char *str, t_matchlist *match);
bool						ft_match_wcard(char *str, t_matchlist *match);
bool						ft_match_qmark(char *str, t_matchlist *match);
bool						ft_match_hook(char *str, t_matchlist *match);
bool						ft_match_rhook(char *str, t_matchlist *match);
char						*ft_expanse_word(char *word, t_42sh *shell);
char						*ft_simple_expanse(char *word, t_42sh *shell);
void						ft_rmquotes_word(char *word);

/*
**							globals
*/

typedef void				(*t_ak)(t_42sh *sh);
typedef void				(*t_test_other)(t_42sh *sh, int *pos);
typedef void				(*t_test)(t_42sh *sh, struct stat info);

/*
**							select_mode
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
void						free_tab(char **str);

/*
**							getenv
*/

char						*ft_getenv(t_env *list, const char *name,
		size_t len, t_var_mark *var);

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
int							check_is_builtin(char *str);

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
void						ft_exit(t_42sh *sh);
void						builtin_exit(t_42sh *sh);
int							check_valid_var(char *str);
int							check_var(t_var_mark **var, char **split);
void						builtin_cd(t_42sh *sh);

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
**							ft_check_exp_ari.c
*/

int							ft_check_exp_ari(char *str);

/*
**							ft_check_var.c
*/

char						*ft_check_var(char *str, t_list_ari **list_var,
		t_42sh *sh);
char						*ft_exp_ary(char *str, t_42sh *sh);
void						check_local_variable(t_42sh *sh, char *str);
int							ft_var_modif(char *str, int i, int j, t_list_ari *new);

/*
** 							ft_utils_exp_ari.c
*/

char						*my_get_var(t_42sh *sh, char *name);
t_list_ari					*ft_add_var_exp(char *str, size_t *i
							, int j, char **nb);
void						ft_replace_vari(t_list_ari *tmp, t_42sh *sh);
void						ft_free_ari(t_list_ari *list, char *str);

/*
**							builtin_cd
*/

int							check_path_opt(char *str, t_42sh *sh, int i);
void						get_list(char *str, t_42sh *sh);
void						ft_dot_dot(t_42sh *sh, t_path **path);
void						join_all(t_42sh *sh);
void						print_error_cd(char *curpath);
int							check_opt_cd(t_42sh *sh, int *i);
char						*cd_exec(t_42sh *sh, int i);
void						exec_cd_path(char *curpath, t_42sh *sh, int opt,
		int i);
void						del_all_path(t_path_mark *path);
void						get_path(char *path, t_42sh *sh, int i);
void						get_dir_cd(char *path, t_42sh *sh, int opt, int i);
void						lst_del_path(t_path **path, t_path *to_del,
							t_path *prev);
char						*getenv_cd(char **env, const char *name,
		size_t len, t_var_mark *var);
void						print_error_alias(char *str, t_42sh *sh, int mode);
int							check_reverse(t_42sh *sh, int *i);
void						check_reverse_end(int reverse, t_42sh *sh);
void						init_path_histo(t_42sh *sh);
int							check_tmp_env(t_42sh *sh, char *str);
void						print_error_export(t_42sh *sh, int i);

#endif
