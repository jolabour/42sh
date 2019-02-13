#include "sh.h"
#include <curses.h>
#include <term.h>

void	init_builtin_tab(t_42sh *sh)
{
	if (!(sh->builtin = malloc(sizeof(char *) * 13)))
		print_error(_ENOMEM, 1);
	sh->builtin[0] = "echo";
	sh->builtin[1] = "cd";
	sh->builtin[2] = "type";
	sh->builtin[3] = "alias";
	sh->builtin[4] = "unalias";
	sh->builtin[5] = "exit";
	sh->builtin[6] = "test";
	sh->builtin[7] = "fc";
	sh->builtin[8] = "hash";
	sh->builtin[9] = "set";
	sh->builtin[10] = "unset";
	sh->builtin[11] = "export";
	sh->builtin[12] = NULL;
}

void		get_term(t_42sh *sh)
{
	//if (tgetent(NULL, ft_getenv(sh->env, "TERM=", 5)) == -1)
	if (tgetent(NULL, getenv("TERM")) == -1)
	{
		ft_putendl("Set term or a valide term.");
		exit(0);
	}
	if (tcgetattr(0, &sh->reset_term) == -1)
	{
		ft_putendl("tcgetattr: Error.");
		exit(0);
	}
	if (tcgetattr(0, &sh->term) == -1)
	{
		ft_putendl("tcgetattr: Error.");
		exit(0);
	}
	/*if (tgetflag("os") != 1)
	{
		ft_putendl("ah");
	}*/
	sh->term.c_lflag &= ~(ICANON);
	sh->term.c_lflag &= ~(ECHO);
	sh->term.c_lflag &= ~(ISIG);
	if (tcsetattr(0, TCSANOW, &sh->term) == -1)
	{
		ft_putendl("tcsetattr: Error.");
		exit(0);
	}
}

void		reset_term(t_42sh *sh)
{
  	if (tcsetattr(0, TCSANOW, &sh->reset_term) == -1)
	{
		ft_putendl("tcsetattr: Error.");
		exit(0);
	}
	exit(0);
}

void		init_alias_list(t_42sh *sh)
{
	if (!(sh->alias = (t_alias_mark*)malloc(sizeof(t_alias_mark))))
		return ;
	sh->alias->size = 0;
}

void		init_shell(t_42sh *sh, char **env)
{
	char *path;
	char *pwd;
	
	sh->env = set_list(env);
	if (!(sh->var_local = malloc(sizeof(t_var_loc))))
		return ;
	path = ft_getenv(sh->env, "PATH=", sizeof("PATH=") - 1);
	if (path)
	{
		if ((sh->bin_dirs = ft_strsplit(path, ':')) == NULL)
			print_error(_ENOMEM, 1);
	}
	pwd = ft_getenv(sh->env, "PWD=", sizeof("PWD=") - 1);
	if (pwd)
	{
		if ((sh->pwd = ft_strdup(pwd)) == NULL)
			print_error(_ENOMEM, 1);
	}
	sh->copy_env = list_to_tab(sh->env, sh->copy_env);
	sh->path_history = ft_strdup(".42sh_history");
	init_builtin_tab(sh);
	sh->line_to_replace = NULL;
	sh->argv = NULL;
	sh->lexer = NULL;
	if (!(sh->argv = malloc(sizeof(t_argv))))
		return ;
	sh->argv->error_code = 0;
	init_alias_list(sh);
	init_hashtable(sh);
	get_term(sh);
}
