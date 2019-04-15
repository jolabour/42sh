/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:34:36 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/16 01:35:36 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXP_H

# define EXP_H

# include "sh.h"

typedef struct s_42sh		t_42sh;

/*
**							enum
*/

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

typedef enum				e_matchtok
{
	MATCH_NONE = 0,
	MATCH_TEXT,
	MATCH_WCARD,
	MATCH_QMARK,
	MATCH_HOOK,
	MATCH_RHOOK
}							t_matchtok;

/*
**							struct
*/

typedef struct				s_txtlist
{
	t_txttype				token;
	char					*data;
	size_t					start;
	size_t					len;
	bool					dquote;
	struct s_txtlist		*next;
}							t_txtlist;

typedef struct				s_spparam
{
	char					c;
	char					*(*f)(t_42sh *);
}							t_spparam;

typedef struct				s_expparam
{
	char					*param;
	int						(*f)(t_txtlist *txt, t_42sh *shell,
							struct s_expparam *expparam);
	char					*word;
}							t_expparam;

typedef struct				s_expparamfunc
{
	char					*str;
	int						(*f)(t_txtlist *txt, t_42sh *shell,
							t_expparam *expparam);
}							t_expparamfunc;

typedef struct				s_matchlist
{
	t_matchtok				token;
	bool					hparam[128];
	char					tparam;
	struct s_matchlist		*next;
}							t_matchlist;

typedef struct				s_class
{
	char					*name;
	char					*chars;
}							t_class;

/*
**							globals
*/

extern t_spparam			g_spparamtab[];
extern int					(*g_txttab[])(char *word, size_t *index,
		t_txtlist **current, bool *dquote);
extern int					(*g_exptab[])(t_txtlist *txt, t_42sh *shell);
extern t_class				g_classestab[];
typedef t_matchlist			*(*t_getmatch)(char *);
extern t_getmatch			g_getmatchtab[];
typedef bool				(*t_match)(char *str, t_matchlist *match);
extern t_match				g_matchtab[];
extern t_expparamfunc		g_expparamtab[];

/*
**							ft_backslash_quotes.c
*/

int							ft_count_quotes(char *word, bool dquote);
char						*ft_backslash_quotes(char *word, bool dquote);

/*
**							ft_cmdsub.c
*/

void						ft_cmdsub_child(int pipefd[2], t_node *ast,
		t_42sh *shell);
void						ft_cmdsub_error(char *command);
char						*ft_cmdsub(char *command, t_42sh *shell,
		bool dquote);

/*
**							ft_cmdsub_parse.c
*/

int							ft_cmdsub_getast(t_ast *ast, t_42sh *shell);
int							ft_cmdsub_parse(t_ast *ast, char *command,
		t_42sh *shell);

/*
**							ft_cmdsub.c
*/

char						*ft_del_ending_newlines(char *str);
char						*ft_cmdsub_read(int fd, pid_t pid);

/*
**							ft_exp.c
*/

int							ft_exp_error(t_txtlist *list, t_txtlist *error);
int							ft_exp(t_txtlist *list, t_42sh *shell);

/*
**							ft_exp_args.c
*/

char						**ft_exp_args_error(char **args);
char						**ft_expanse_args(char **args, t_42sh *shell);

/*
**							ft_exp_brace.c
*/

int							ft_exp_brace_error(t_txtlist *txt);
int							ft_exp_brace(t_txtlist *txt, t_42sh *shell);

/*
**							ft_exp_cmdsub.c
*/

int							ft_exp_sub(t_txtlist *txt, t_42sh *shell);
int							ft_exp_bquote(t_txtlist *txt, t_42sh *shell);

/*
**							ft_exp_others.c
*/

int							ft_exp_text(t_txtlist *txt, t_42sh *shell);
int							ft_exp_var(t_txtlist *txt, t_42sh *shell);
int							ft_exp_expr(t_txtlist *txt, t_42sh *shell);

/*
**							ft_exp_parse.c
*/

void						ft_parse_error(t_txtlist *list);
t_txtlist					*ft_parse_check(t_txtlist *list);
t_txtlist					*ft_parse_word(char *word);

/*
**							ft_exp_parse_text.c
*/

int							ft_parse_backslash(char *word, size_t *index,
		t_txtlist **current, bool *dquote);
int							ft_parse_quote(char *word, size_t *index,
		t_txtlist **current, bool *dquote);
int							ft_parse_text(char *word, size_t *index,
		t_txtlist **current, bool *dquote);

/*
**							ft_exp_parse_tilde.c
*/

int							ft_parse_tilde(char *word, size_t *index,
		t_txtlist **current, bool *dquote);

/*
**							ft_exp_parse_tools.c
*/

t_txtlist					*ft_new_txtlist(void);
t_txtlist					*ft_add_txtlist(char *data, t_txttype token,
		t_txtlist **to, bool dquote);

/*
**							ft_exp_parse_var.c
*/

void						ft_parse_sub_mode(char *word, size_t *index,
		char *quote);
int							ft_parse_brace_var(char *word, size_t *index,
		t_txtlist **current);
int							ft_parse_par_var(char *word, size_t *index,
		t_txtlist **current);
int							ft_parse_var(char *word, size_t *index,
		t_txtlist **current, bool *dquote);
int							ft_parse_bquote(char *word, size_t *index,
		t_txtlist **current, bool *dquote);

/*
**							ft_exp_spparam.c
*/

char						*ft_spparam_dollar(t_42sh *shell);
char						*ft_spparam_qmark(t_42sh *shell);
char						*ft_spparam_bang(t_42sh *shell);
char						*ft_spparam_zero(t_42sh *shell);
typedef char				*(*t_getspparam)(t_42sh *);
t_getspparam				ft_get_spparam(char c);

/*
**							ft_exp_tilde.c
*/

char						*ft_tilde_alone(t_42sh *shell);
char						*ft_tilde_user(t_txtlist *txt);
int							ft_exp_tilde(t_txtlist *txt, t_42sh *shell);

/*
**							ft_expanse.c
*/

char						**ft_init_args(t_node *current);
char						*ft_expanse_word(char *word, t_42sh *shell);
char						**ft_command_to_args(t_node *current,
		t_42sh *shell);
char						*ft_simple_expanse(char *word, t_42sh *shell);

/*
**							ft_expparam_equal.c
*/

void						ft_expparam_assign(t_expparam *expparam,
		t_42sh *shell);
int							ft_expparam_cnequal(t_txtlist *txt, t_42sh *shell,
		t_expparam *expparam);
int							ft_expparam_equal(t_txtlist *txt, t_42sh *shell,
		t_expparam *expparam);

/*
**							ft_expparam_minus.c
*/

int							ft_expparam_cnminus(t_txtlist *txt, t_42sh *shell,
		t_expparam *expparam);
int							ft_expparam_minus(t_txtlist *txt, t_42sh *shell,
		t_expparam *expparam);

/*
**							ft_expparam_nofunc.c
*/

int							ft_expparam_nofunc(t_txtlist *txt, t_42sh *shell,
		t_expparam *expparam);

/*
**							ft_expparam_plus.c
*/

int							ft_expparam_cnplus(t_txtlist *txt, t_42sh *shell,
		t_expparam *expparam);
int							ft_expparam_plus(t_txtlist *txt, t_42sh *shell,
		t_expparam *expparam);

/*
**							ft_expparam_pcent.c
*/

char						*ft_match_rmslsuffix(char *param, char *word);
int							ft_expparam_pcent(t_txtlist *txt, t_42sh *shell,
		t_expparam *expparam);
char						*ft_match_rmlgsuffix(char *param, char *word);
int							ft_expparam_dpcent(t_txtlist *txt, t_42sh *shell,
		t_expparam *expparam);

/*
**							ft_expparam_qmark.c
*/

int							ft_expparam_qmark_error(t_expparam *expparam,
		char *error);
int							ft_expparam_cnqmark(t_txtlist *txt, t_42sh *shell,
		t_expparam *expparam);
int							ft_expparam_qmark(t_txtlist *txt, t_42sh *shell,
		t_expparam *expparam);

/*
**							ft_expparam_sharp.c
*/

int							ft_expparam_sharp_noparam(t_txtlist *txt,
		t_42sh *shell, t_expparam *expparam);
char						*ft_match_rmslprefix(char *param, char *word);
int							ft_expparam_sharp(t_txtlist *txt, t_42sh *shell,
		t_expparam *expparam);
char						*ft_match_rmlgprefix(char *param, char *word);
int							ft_expparam_dsharp(t_txtlist *txt, t_42sh *shell,
		t_expparam *expparam);

/*
**							ft_expparam_tools.c
*/

int							ft_expparam_getvar(char *exp,
		t_expparam *expparam);
void						ft_expparam_free(t_expparam *expparam);
int							ft_expparam_getfunc(char *exp,
		t_expparam *expparam);

/*
**							ft_field_split.c
*/

size_t						ft_count_field_size(char *word, char *sep);
int							ft_count_fields(char *word, char *sep);
char						**ft_field_split_word(char *word, char *sep);
char						**ft_field_split(char **args, t_42sh *shell);

/*
**							ft_gather_splits.c
*/

int							ft_count_args(char ***splits);
char						**ft_gather_splits(char ***splits);

/*
**							ft_getmatch.c
*/

t_matchlist					*ft_new_match(t_matchtok token);
t_matchlist					*ft_getmatch_wcard(char *word);
t_matchlist					*ft_getmatch_qmark(char *word);
t_matchlist					*ft_getmatch_text(char *word);
t_matchlist					*ft_getmatch_list(char *word);

/*
**							ft_getmatch_free.c
*/

void						ft_getmatch_free(t_matchlist *list);

/*
**							ft_getmatch_hook.c
*/

int							ft_getmatch_hookdash(char *word,
		t_matchlist *match);
int							ft_getmatch_hookhook(char *word,
		t_matchlist *match);
int							ft_getmatch_hooknormal(char *word,
		t_matchlist *match);
int							ft_getmatch_hook_init(t_matchlist *match,
		char *word);
t_matchlist					*ft_getmatch_hook(char *word);

/*
**							ft_getvar.c
*/

char						*ft_getvar(char *var, t_42sh *shell);

/*
**							ft_match.c
*/

bool						ft_match_end(char *str, t_matchlist *match);
bool						ft_match_text(char *str, t_matchlist *match);
bool						ft_match_wcard(char *str, t_matchlist *match);
bool						ft_match_qmark(char *str, t_matchlist *match);

/*
**							ft_match_hook.c
*/

bool						ft_match_hook(char *str, t_matchlist *match);
bool						ft_match_rhook(char *str, t_matchlist *match);

/*
**							ft_revmatch.c
*/

t_matchlist					*ft_revmatch_rev(t_matchlist *l1);
t_matchlist					*ft_revmatch(t_matchlist *list);

/*
**							ft_rmquotes.c
*/

int							ft_rmquotes_backslash_condition(char *word, int i,
		char quote);
void						ft_rmquotes_word(char *word);
void						ft_rmquotes_args(char **args);

/*
**							ft_txt_join.c
*/

size_t						ft_txt_len(t_txtlist *list);
char						*ft_txt_join(t_txtlist *list);

#endif
