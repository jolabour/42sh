/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_last_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:37:26 by ttresori          #+#    #+#             */
/*   Updated: 2019/02/18 23:38:14 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"

static void	create_tmp_file(char *to_write)
{
	int fd;

	fd = open(PATH_TMP, O_CREAT, ~O_RDWR);
	close(fd);
	fd = open(PATH_TMP, O_RDWR, O_APPEND);
	ft_putstr_fd(to_write, fd);
	ft_putstr_fd("\0", fd);
	close(fd);
}

static int	fc_edit(t_42sh *sh, char *to_edit)
{
	pid_t	father;
	int		status;
	char    **to_ed;

	status = 0;
	if (!(to_ed = (char**)malloc(sizeof(char*) * 3)))
		return (-1);
	FC_EDIT_EDITOR == NULL ? (to_ed[0] = NULL) : (to_ed[0] = ft_strdup(FC_EDIT_EDITOR));
	FC_EDIT_PATH == NULL ? (to_ed[1] = NULL) : (to_ed[1] = ft_strdup(PATH_TMP));
	to_ed[2] = NULL;
	create_tmp_file(to_edit);
	father = fork();
	if (father > 0)
		wait(0);
	if (father == 0)
	{
		if ((status = execve(FC_EDIT_PATH, to_ed, sh->copy_env)) == -1)
			ft_putendl_fd("///////////", 2);
		ft_free_split(to_ed);
		return (1);
	}
	ft_free_split(to_ed);
	return (1);
}

static char	*check_dup(char *to_check)
{
	int		fd;
	int		i;
	char	*in_file;
	char	c;


	fd = open(PATH_TMP, O_RDWR);
	i = 0;
	c = '\0';
	while (read(fd, &c, 1) > 0)
		i++;
	close(fd);
	if (!(in_file = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	fd = open(PATH_TMP, O_RDONLY);
	i = 0;
	c = '\0';
	while (read(fd, &c, 1) > 0)
	{
		in_file[i] = c;
		c = '\0';
		i++;
	}
	in_file[i - 1] = '\0';
	close(fd);
	if (to_check && in_file && ft_strcmp(to_check, in_file) == 0)
	{
		ft_putl_green("Same");
		free(in_file);
		return (NULL);
	}
	return (in_file);
}

void	edit_last_command(t_42sh *sh)
{
	t_history   *tmp;
	char        *is_modify;
	int         i;

	tmp = sh->history_mark->begin->next;
	i = 0;
	if ((fc_edit(sh, tmp->str)) == 1)
	{
		if ((is_modify = check_dup(tmp->str)) != NULL)
		{
			ft_strdel(&sh->stdin->input);
			sh->stdin->input = ft_strdup(is_modify);
			check_substitute_history(sh);
			if (sh->argv->argv)
				ft_free_split(sh->argv->argv);
			sh->argv->argv = ft_strsplitset(sh->stdin->input, " \n\t");
			sh->valide_path = check_access(sh, 0);
			free(is_modify);
			get_fork(sh);
		}
		unlink(PATH_TMP);
	}
}
