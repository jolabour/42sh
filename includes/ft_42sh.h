/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_42sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:10:16 by geargenc          #+#    #+#             */
/*   Updated: 2019/03/14 23:55:36 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_42SH_H

# define FT_42SH_H

# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>
# include <sys/stat.h>

# include "libft.h"

typedef enum			e_tok
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
}						t_tok;

typedef struct			s_toktab
{
	char				*str;
	t_tok				token;
}						t_toktab;

typedef struct			s_toklist
{
	t_tok				token;
	size_t				start;
	size_t				len;
	struct s_toklist	*next;
}						t_toklist;

typedef struct			s_node
{
	t_tok				token;
	char				*data;
	struct s_node		*left;
	struct s_node		*right;
	struct s_node		*parent;
	struct s_node		*redir;
}						t_node;

typedef struct			s_main
{
	char				*ttyname;
	struct winsize		winsize;
}						t_main;

char					*ft_strjoinfree(char *s1, char *s2, unsigned int which);


/*
**						lexer
*/

int						ft_lex_operator(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_notoperator(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_newline(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_backslash(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_quote(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_dquote(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_dollar(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_bquote(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_ionumber(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_newoperator(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_blank(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_sharp(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_word(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_newword(char **input, size_t *index,
						t_toklist **current);
t_toklist				*ft_lexer(char **input);
void					ft_print_toklist(char *input, t_toklist *list);

/*
**						ast
*/

int						ft_ast_word(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_newline(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_io_number(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_badtoken(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_pipe(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_separator(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_redir(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_lpar(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_rpar(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_and_or(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_heredoc(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_closefd(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_lbrace(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_rbrace(t_node **begin, t_node **current,
						t_node **list);
t_node					*ft_toklist_to_node(char *input, t_toklist *list);
t_node					*ft_build_ast(t_node *list);

typedef struct			s_tokcond
{
	int					(*cond)(char **, size_t *, t_toklist **);
	int					dquote_mode;
	int					sub_mode;
}						t_tokcond;

typedef struct			s_proclist
{
	pid_t				pid;
	t_node				*command;
	int					status;
	char				*path;
	char				**args;
	struct s_proclist	*next;
}						t_proclist;

typedef struct			s_joblist
{
	pid_t				pgid;
	t_proclist			*process;
	t_node				*command;
	int					num;
	struct s_joblist	*next;
}						t_joblist;

typedef struct			s_tmpfd
{
	int					initial;
	int					tmp;
	int					cloexec;
	struct s_tmpfd		*next;
}						t_tmpfd;

typedef struct			s_shell
{
	pid_t				pgid;
	int					forked;
	t_joblist			*jobs;
	pid_t				pid;
	int					retval;
	int					foreground;
	struct termios		term;
	t_tmpfd				*tmp_fds;
}						t_shell;

void					ft_init(t_shell *shell);

/*
**						exe
*/

int						ft_exe_badtoken(t_node *current, t_shell *shell);
int						ft_exe_pipe(t_node *current, t_shell *shell);
int						ft_exe_and(t_node *current, t_shell *shell);
int						ft_exe_semi(t_node *current, t_shell *shell);
int						ft_exe_great(t_node *current, t_shell *shell);
int						ft_exe_less(t_node *current, t_shell *shell);
int						ft_exe_rpar(t_node *current, t_shell *shell);
int						ft_exe_and_if(t_node *current, t_shell *shell);
int						ft_exe_or_if(t_node *current, t_shell *shell);
int						ft_exe_dgreat(t_node *current, t_shell *shell);
int						ft_exe_lessand(t_node *current, t_shell *shell);
int						ft_exe_lessanddash(t_node *current, t_shell *shell);
int						ft_exe_greatand(t_node *current, t_shell *shell);
int						ft_exe_greatanddash(t_node *current, t_shell *shell);
int						ft_exe_lessgreat(t_node *current, t_shell *shell);
int						ft_exe_dless(t_node *current, t_shell *shell);
int						ft_exe_rbrace(t_node *current, t_shell *shell);
int						ft_exe_command(t_node *current, t_shell *shell);


extern char				*g_tokstr[];
extern t_toktab			g_toktab[];
extern t_tokcond		g_tokcond[];
extern int				(*g_asttab[])(t_node **begin, t_node **current,
						t_node **list);
extern int				(*g_exetab[])(t_node *current, t_shell *shell);

#endif
