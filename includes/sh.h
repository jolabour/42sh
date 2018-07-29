/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 04:26:44 by jolabour          #+#    #+#             */
/*   Updated: 2018/07/29 10:28:45 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SH_H
# define SH_H

# include "libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <term.h>
# include <curses.h>
# include <pwd.h>
# include <termios.h>

typedef enum		e_errno_val
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
}					t_errno;

static t_errno		g_errno;
static const char	*g_errors[_ERRNO_VALUES];

typedef struct		s_env
{
	char			*str;
	struct s_env	*next;
}					t_env;

typedef struct		s_42sh
{
	char			input[256];
	char			**arg;
	char			*pwd;
	char			**bin_dirs;
	char			**copy_env;
	t_env			*env;
}					t_42sh;

/*
** errno
*/

void				init_error_tab(void);
void				print_error(int error_code);
void				print_error_and_exit(int error_code);
void				print_error_first(int error_code);
int					ft_set_errno(int n);

/*
 ** process
 */

void			process(t_42sh *sh);

/*
** prompt
*/

void			prompt(t_env *list);

/*
 ** list
 */

int				len_list(t_env *env);
void			list_to_tab(t_env *env, char **copy_env);
t_env			*create_node(char *str);
void			lst_push(t_env **head, t_env *new);
t_env			*set_list(char **env);

/*
 ** getenv
 */

char			*ft_getenv(t_env *list, const char *name, size_t len);

/*
** stdin
*/

void			get_line(char *line);

/*
** init_shell
*/

void			init_shell(t_42sh *sh, char **env);

#endif
