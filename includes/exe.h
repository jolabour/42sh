/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 08:59:44 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/20 05:12:33 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H

# define EXE_H

# include "sh.h"

typedef struct s_42sh		t_42sh;

/*
**							struct
*/

typedef struct				s_tmpfd
{
	int						initial;
	int						tmp;
	int						cloexec;
	struct s_tmpfd			*next;
}							t_tmpfd;

typedef struct				s_bttab
{
	char					*name;
	void					(*f)(t_42sh *);
}							t_bttab;

/*
**							globals
*/

extern int					(*g_exetab[])(t_node *current, t_42sh *shell);
extern t_bttab				g_bttab[];

/*
**							ft_exe_assigns.c
*/

void						ft_add_tmp_env(char *var, char *value,
		t_42sh *shell);
int							ft_tmp_assigns(t_node *current, t_42sh *shell);
int							ft_sustained_assigns(t_node *current,
		t_42sh *shell);
int							ft_assigns(t_node *current, t_42sh *shell);

/*
**							ft_exe_builtin.c
*/

typedef void				(*t_btn)(t_42sh *sh);

t_btn						ft_isbuiltin(char *word);
int							ft_count_argvsize(char **args);
int							ft_exe_builtin(t_node *current, t_42sh *shell,
		void (*f)(t_42sh *));

/*
**							ft_exe_command.c
*/

char						*ft_exe_command_get_path(t_42sh *shell);
void						get_path_ht(t_42sh *shell);
int							ft_exe_command_ht(t_node *current, t_42sh *shell);
int							ft_exe_command(t_node *current, t_42sh *shell);

/*
**							ft_exe_compound.c
*/

int							ft_exe_rpar(t_node *current, t_42sh *shell);
int							ft_exe_rbrace(t_node *current, t_42sh *shell);

/*
**							ft_exe_exit.c
*/

void						ft_execve_exit(char *path, char **argv,
		char **envp);
int							ft_pipe_exit(int pipefd[2]);
pid_t						ft_fork_exit(void);
int							ft_dup_exit(int fd);
int							ft_dup2_exit(int fd1, int fd2);

/*
**							ft_exe_file.c
*/

void						ft_exe_file_error(char *path, char *error);
int							ft_exe_file_check(char *path);
int							ft_exe_file(t_node *current, t_42sh *shell,
		char *path, char **args);

/*
**							ft_exe_redir.c
*/

int							ft_exe_great(t_node *current, t_42sh *shell);
int							ft_exe_less(t_node *current, t_42sh *shell);
int							ft_exe_dless(t_node *current, t_42sh *shell);
int							ft_exe_dgreat(t_node *current, t_42sh *shell);
int							ft_exe_lessgreat(t_node *current, t_42sh *shell);

/*
**							ft_exe_redirand.c
*/

int							ft_exe_lessand(t_node *current, t_42sh *shell);
int							ft_exe_lessanddash(t_node *current, t_42sh *shell);
int							ft_exe_greatand(t_node *current, t_42sh *shell);
int							ft_exe_greatanddash(t_node *current, t_42sh *shell);

/*
**							ft_exe_redirerror.c
*/

int							ft_open_error(char *path, int options, char *unexp);
int							ft_ambigous_error(char *fd, char *unexp);
int							ft_badfd_error(char *fd, char *unexp);

/*
**							ft_exe_separators.c
*/

int							ft_exe_pipe(t_node *current, t_42sh *shell);
int							ft_exe_and(t_node *current, t_42sh *shell);
int							ft_exe_semi(t_node *current, t_42sh *shell);
int							ft_exe_and_if(t_node *current, t_42sh *shell);
int							ft_exe_or_if(t_node *current, t_42sh *shell);

/*
**							ft_exe_tmpfd.c
*/

int							ft_dup_tmp_fd(int fd);
void						ft_build_tmp_fd(int fd, t_tmpfd **begin);
void						ft_reset_tmp_fd(t_tmpfd *begin);

#endif
