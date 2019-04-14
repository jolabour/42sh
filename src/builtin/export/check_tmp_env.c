#include "sh.h"

int				check_tmp_env(t_42sh *sh, char *str)
{
	char		*name;
	char		*to_export;
	char		**split;
	t_env		*new;
	char		*join;

	name = ft_strjoin(str, "=");
	if ((to_export = getenv_cd(sh->copy_env, name, ft_strlen(name), NULL)) == NULL)
	{
		free(name);
		return (0);
	}
	split = ft_malloc_exit(sizeof(char*) * 3);
	split[0] = ft_strdup(str);
	split[1] = ft_strdup(to_export);
	split[2] = NULL;
	if (check_env(&sh->env, split) == 0)
	{
		join = ft_strjoin(name, to_export);
		new = create_node(join);
		lst_push(&sh->env, new);
		free(join);
	}
	ft_free_split(split);
	free(name);
	return (1);
}
