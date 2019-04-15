/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expanse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:26:39 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/16 01:43:50 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char			**ft_init_args(t_node *current)
{
	char		**args;
	t_node		*tmp;
	int			i;

	i = 0;
	tmp = current;
	while ((tmp = tmp->right))
		i++;
	args = (char **)ft_malloc_exit((i + 1) * sizeof(char *));
	i = 0;
	tmp = current;
	while ((tmp = tmp->right))
	{
		if (!(args[i] = ft_strdup(tmp->data)))
			exit(2);
		i++;
	}
	args[i] = NULL;
	return (args);
}

char			*ft_expanse_word(char *word, t_42sh *shell)
{
	t_txtlist	*list;
	char		*result;

	list = ft_parse_word(word);
	if (ft_exp(list, shell))
	{
		shell->stopexe = true;
		return (NULL);
	}
	result = ft_txt_join(list);
	return (result);
}

char			**ft_command_to_args(t_node *current, t_42sh *shell)
{
	char		**args;

	args = ft_init_args(current);
	if (!ft_expanse_args(args, shell))
		return (NULL);
	args = ft_field_split(args, shell);
	ft_rmquotes_args(args);
	return (args);
}

char			*ft_simple_expanse(char *word, t_42sh *shell)
{
	char		*new;

	if ((new = ft_expanse_word(word, shell)))
		ft_rmquotes_word(new);
	return (new);
}
