/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 19:41:02 by ttresori          #+#    #+#             */
/*   Updated: 2019/01/25 18:29:52 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "sh.h"

void	modify_last_history(t_42sh *sh)
{
  int i;
  int i2;
  int size;
  int nb_replace;
  int fd;

  i = 0;
  i2 = 0;
  size = 0;
  fd = 0;
  nb_replace = 0;
  add_to_list(sh, sh->history_mark->last_str);
  fd = open(sh->path_history, O_RDWR);
  lseek(fd, sh->history_mark->size + 1, SEEK_END);
  ft_putstr_fd(sh->history_mark->last_str, fd);
  ft_putendl_fd("\0", fd);
  free(sh->history_mark->last_str);
  sh->history_mark->last_str = NULL;
  close(fd);
}

char *search_history_begin(t_42sh *sh, int nb)
{
    int            i;
    t_history   *tmp;
    char        *substitute;
    int         size;

    if (nb == 0)
        return (NULL);
    i = 1;
    tmp = NULL;
    substitute = NULL;
    size = sh->history_mark->size - 1;
    tmp = sh->history_mark->last;
    while (nb != 1)
    {
        if (i >= size)
            return (NULL);
        tmp = tmp->prev;
        nb--;
        i++;
    }
    substitute = ft_strdup(tmp->str);
    return (substitute);
}

char *search_str_input(t_42sh *sh, int start, int *nb_del)
{
    int     i;
    char    *str_to_find;
    char    *sub;

    str_to_find = NULL;
    sub = NULL;
    i = 0;
    if (!(str_to_find = (char*)malloc(sizeof(char) 
        * (ft_strlen(sh->stdin->input) + 1))))
        print_error(_ENOMEM, 1);
   while (sh->stdin->input[start] 
        && (sh->stdin->input[start] != ' ' 
        && sh->stdin->input[start] != '\t')
        && sh->stdin->input[start] != '!'
        && sh->stdin->input[start] != '\n')
    {
        str_to_find[i] = sh->stdin->input[start];
        i++;
        start++;
    }
    str_to_find[i] = '\0';
    *nb_del = ft_strlen(str_to_find) + 1;
    sub = search_history_char(sh, &str_to_find);
    ft_strdel(&str_to_find);
    return (sub);
}

char *search_history_char(t_42sh *sh, char **to_find)
{
    char        *sub;
    int         len_str_to_find;
    int         size_list;
    t_history   *tmp;

    sub = NULL;
    tmp = NULL;
    tmp = sh->history_mark->begin->next;
    size_list = sh->history_mark->size - 1;
    len_str_to_find = ft_strlen(*to_find);
    while (size_list >= 1)
    {
        if (ft_strncmp(*to_find, tmp->str, len_str_to_find) == 0)
            return ((sub = ft_strdup(tmp->str)));
        tmp = tmp->next;
        size_list--;
    }
    ft_puts_green("OK");
    return (NULL);
}

char *search_history_last(t_42sh *sh, int nb)
{
    t_history   *tmp;
    char        *substitute;
    int         size;
    if (nb == 0)
        return (NULL);
    tmp = NULL;
    substitute = NULL;
    size = sh->history_mark->size - 1;
    tmp = sh->history_mark->begin->next;
    if (nb == 0)
        return (NULL);
    while (nb != -1)
    {
        if (size <= 1)
            return (NULL);
        tmp = tmp->next;
        nb++;
        size--;
    }
    substitute = ft_strdup(tmp->str);
    return (substitute);
}

void	get_substitute(t_42sh *sh, int i, char *substitute, int nb_del)
{
  char *tmp;
  char *tmp2;
  char *tmp3;

  tmp = NULL;
  tmp2 = NULL;
  tmp3 = NULL;
  if (i != 0)
  {
    tmp = ft_strsub(sh->stdin->input, 0, i);
    tmp3 = ft_strjoin(tmp, substitute);
  }
  else
  {
    tmp3 = ft_strdup(substitute);
    tmp = ft_strdup("");
    }
  tmp2 = ft_strsub(sh->stdin->input, i + nb_del, ft_strlen(sh->stdin->input)
       - ft_strlen(tmp) - nb_del);
  ft_strdel(&sh->stdin->input);
  sh->stdin->input = ft_strjoin(tmp3, tmp2);
  ft_puts_red(sh->stdin->input);
  ft_strdel(&tmp);
  ft_strdel(&tmp2);
  ft_strdel(&tmp3);
}

int get_nb_history(t_42sh *sh, int pos, int *nb_del)
{
    int i;
    int nb;
    char *nb_to_find;

    i = 0;
    nb = 0;
    if (!(nb_to_find = (char*)malloc(sizeof(char) * ft_strlen(sh->stdin->input))))
        print_error(_ENOMEM, 1);
    if (sh->stdin->input[pos + 1] == '-' && (sh->stdin->input[pos + 2] >= '0' 
    && sh->stdin->input[pos + 2] <= '9'))
    {
        nb_to_find[i] = '-';
        i++;
        pos++;
    }
    while(sh->stdin->input[pos + 1] && (sh->stdin->input[pos + 1] >= '0' 
    && sh->stdin->input[pos + 1] <= '9'))
    {
        nb_to_find[i] = sh->stdin->input[pos + 1];
        i++;
        pos++;
    }
    nb_to_find[i] = '\0';
    *nb_del = ft_strlen(nb_to_find) + 1;
    nb = ft_atoi(nb_to_find);
    ft_strdel(&nb_to_find);
    return (nb);
}
