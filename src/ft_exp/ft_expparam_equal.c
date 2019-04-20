/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expparam_equal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:47:58 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/20 05:48:51 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_expparam_assign(t_expparam *expparam, t_42sh *shell)
{
	char		*assign;
	size_t		param_len;

	if (ft_isalpha(expparam->param[0]) || expparam->param[0] == '_')
	{
		param_len = ft_strlen(expparam->param);
		assign = (char *)ft_malloc_exit((param_len + ft_strlen(expparam->word)
			+ 2) * sizeof(char));
		ft_strcpy(assign, expparam->param);
		assign[param_len] = '=';
		ft_strcpy(assign + param_len + 1, expparam->word);
		check_local_variable(shell, assign);
		free(assign);
	}
}

int				ft_expparam_cnequal(t_txtlist *txt, t_42sh *shell,
				t_expparam *expparam)
{
	char		*word;

	if (!expparam->param || !(word = ft_simple_expanse(expparam->word, shell)))
	{
		ft_expparam_free(expparam);
		return (ft_exp_brace_error(txt));
	}
	free(expparam->word);
	expparam->word = word;
	txt->data = ft_getvar(expparam->param, shell);
	if (txt->data && !txt->data[0])
	{
		free(txt->data);
		txt->data = NULL;
	}
	if (txt->data)
		txt->data = ft_backslash_quotes(txt->data, txt->dquote);
	else
	{
		ft_expparam_assign(expparam, shell);
		txt->data = ft_backslash_quotes(expparam->word, txt->dquote);
		expparam->word = NULL;
	}
	ft_expparam_free(expparam);
	return (0);
}

int				ft_expparam_equal(t_txtlist *txt, t_42sh *shell,
				t_expparam *expparam)
{
	char		*word;

	if (!expparam->param || !(word = ft_simple_expanse(expparam->word, shell)))
	{
		ft_expparam_free(expparam);
		return (ft_exp_brace_error(txt));
	}
	free(expparam->word);
	expparam->word = word;
	txt->data = ft_getvar(expparam->param, shell);
	if (txt->data)
		txt->data = ft_backslash_quotes(txt->data, txt->dquote);
	else
	{
		ft_expparam_assign(expparam, shell);
		txt->data = ft_backslash_quotes(expparam->word, txt->dquote);
		expparam->word = NULL;
	}
	ft_expparam_free(expparam);
	return (0);
}
