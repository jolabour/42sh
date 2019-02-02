#include "sh.h"

static char *search_in_alias(t_42sh *sh, char *to_sub)
{
    int i;
    t_alias *tmp;

    tmp = NULL;
    i = 0;
    if (sh->alias->size == 0)
        return (NULL);
    else
        {
            tmp = sh->alias->begin;
            while (tmp)
            {
                if (ft_strcmp(to_sub, tmp->to_sub) == 0)
                {
                    return (tmp->to_sub);
                }
                i++;
                tmp = tmp->next;
            }
        }
    return (NULL);
}

static int     search_alias(t_42sh *sh, char *name)
{
    t_alias *tmp;
    int     size;

    tmp = NULL;
    size = 0;
    tmp = sh->alias->begin;
    size = sh->alias->size;
    while (size > 0)
    {
        if (ft_strcmp(tmp->to_sub, name) == 0)
            return (size);
        tmp = tmp->next;
        size--;
    }
    return (0);
}

static void    add_alias(t_42sh *sh, char *name, char *value)
{
    t_alias *tmp;
    int     size;

    tmp = NULL;
    tmp = sh->alias->begin;
    size = sh->alias->size;
    while (size > 0)
    {
        sh->alias->begin = sh->alias->begin->next;
        size--;
    }
    sh->alias->begin->to_sub = ft_strdup(name);
    sh->alias->begin->sub = ft_strdup(value);
    sh->alias->size++;
}

void    builtin_alias(t_42sh *sh)
{
    char **split;
    char *substitute;

    split = NULL;
    if (sh->argv->argv[1] == NULL)
        return ;
    split = ft_strsplitset(sh->argv->argv[1], "=");
    if (split[1] == NULL)
        {
            if (!((substitute = search_in_alias(sh, sh->argv->argv[1]))))
            {
                ft_putstr("\n");
                ft_putstr("42sh: alias: ");
                ft_putstr(sh->argv->argv[1]);
                ft_putendl(": not found");
                return ;
            }
            else
            {
                free(sh->argv->argv[0]);
                sh->argv->argv[0] = ft_strdup(substitute);
                ft_puts_yellow(sh->argv->argv[0]);
                free(substitute);
                ft_free_split(split);
            }
        }
    else
    {
        if (search_alias(sh, split[0]) == 0)
            add_alias(sh, split[0], split[1]);
    }
}