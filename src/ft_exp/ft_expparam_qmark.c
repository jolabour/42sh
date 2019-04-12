/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expparam_qmark.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:49:38 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:52:44 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_expparam_qmark_error(t_expparam *expparam, char *error)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putstr_fd(expparam->param, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (expparam->word && expparam->word[0])
		ft_putstr_fd(expparam->word, STDERR_FILENO);
	else
		ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_expparam_free(expparam);
	return (-1);
}

int				ft_expparam_cnqmark(t_txtlist *txt, t_42sh *shell,
				t_expparam *expparam)
{
	char		*word;

	if (!expparam->param || !(word = ft_expanse_word(expparam->word, shell)))
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
		return (ft_expparam_qmark_error(expparam, "parameter null or not set"));
	ft_expparam_free(expparam);
	return (0);
}

int				ft_expparam_qmark(t_txtlist *txt, t_42sh *shell,
				t_expparam *expparam)
{
	char		*word;

	if (!expparam->param || !(word = ft_expanse_word(expparam->word, shell)))
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
		return (ft_expparam_qmark_error(expparam, "parameter not set"));
	ft_expparam_free(expparam);
	return (0);
}
