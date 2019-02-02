#include "sh.h"

static char			*get_line_ctrlr(char *arg, int pos)
{
	long	buf;
	int		i;

	buf = 0;
    if ((i = read(0, &buf, 6)) > 0)
	{
        if (buf == '\n')
            return (NULL);
        if (pos == 0)
            arg = ft_realloc(arg, 0, 1);
        else
            arg = ft_realloc(arg, pos, pos + 1);
        arg[pos] = buf;
        return (arg);
	}
    return (NULL);
}

static int check_following(char *to_find, char *search, int len_check, int start_search)
{
    int i;

    i = 0;
    while(len_check >= 0)
    {
        if (to_find[i] != search[start_search++])
            return (-1);
        len_check--;
        i++;
    }
    return (1);
}

int         is_in_str(char *to_find, char *search, int len_check)
{
    int i;

    i = 0;
    while (search[i])
    {
        if (search[i] == to_find[0])
            if (check_following(to_find, search, len_check, i) == 1)
                return (0);
       i++;
    }
    return (-1);
}

static char *search_history_ctrl_r(t_42sh *sh, char *to_find, int len_str_to_find)
{
    char        *sub;
    int         size_list;
    t_history   *tmp;

    sub = NULL;
    tmp = NULL;
    tmp = sh->history_mark->begin;
    size_list = sh->history_mark->size;
    while (size_list > 0)
    {
        if (is_in_str(to_find, tmp->str, len_str_to_find) == 0)
            return ((sub = ft_strdup(tmp->str)));
        tmp = tmp->next;
        size_list--;
    }
    return (NULL);
}

void    clean_line_lentoback(int len_to_left)
{
    while (len_to_left >= 0)
    {
        tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
        len_to_left--;
    }
    tputs(tgetstr("dl", NULL), 0, putchar_custom);
}

void     ctrlr_action(t_42sh *sh)
{
    char    *arg;
    char    *dup;
    int     i;
    static  int mess_print = 0;

    arg = NULL;
    dup = NULL;
    i = 0;
    if (!(arg = (char*)malloc(sizeof(char) * 0)))
        return ;
    if (mess_print == 0)
    {
        ft_putchar('\n');
        ft_puts_green("bck-i-search: ");
    }
    while (42)
    {
        if (!(arg = get_line_ctrlr(arg, i)))
        {
            if (!dup) //not find
            {
                if (mess_print == 0)
                {
                    if (!dup)
                        clean_line_lentoback(i + 14); //len_mess_print
                    else
                        clean_line_lentoback(ft_strlen(dup) + 14); //len_mess_print
                }
                else
                {
                    if (!dup)
                        clean_line_lentoback(i + 14); //len_mess_print
                    else
                        clean_line_lentoback(ft_strlen(dup) + 14); //len_mess_print
                }
                mess_print = 1;
                ft_puts_green("failing bck-i-search: ");
                free(arg);
                ctrlr_action(sh);
            }
            free(arg);
            arg = NULL;
            if (mess_print == 0)
                    clean_line_lentoback(ft_strlen(dup) + 14); //len_mess_print
            else
                    clean_line_lentoback(ft_strlen(dup) + 23);
            get_substitute(sh, i, dup, 0);
            free(dup);
            return ;
        }
        if (dup)
            free(dup);
        if ((dup = search_history_ctrl_r(sh, arg, i)))
        {
            if (mess_print == 0)
            {
                if (!dup)
                    clean_line_lentoback(i + 14); //len_mess_print
                else
                    clean_line_lentoback(ft_strlen(dup) + 14); //len_mess_print
            }
            else
            {
                if (!dup)
                    clean_line_lentoback(i + 14); //len_mess_print
                 else
                    clean_line_lentoback(ft_strlen(dup) + 14); //len_mess_print
            }
            ft_puts_green("bck-i-search: ");
            ft_putstr(dup);
            mess_print = 0;
        }
        i++;
    }
}