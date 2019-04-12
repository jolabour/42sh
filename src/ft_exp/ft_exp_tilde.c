/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:38:50 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:51:31 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char				*ft_tilde_alone(t_42sh *shell)
{
	char			*path;
	struct passwd	*pw;

	path = ft_getvar("HOME", shell);
	if (!path)
	{
		pw = getpwnam(getlogin());
		if (pw)
			path = ft_strdup(pw->pw_dir);
	}
	return (path);
}

char				*ft_tilde_user(t_txtlist *txt)
{
	char			*user;
	struct passwd	*pw;

	user = ft_strsub(txt->data, txt->start + 1, txt->len - 1);
	if (user)
	{
		pw = getpwnam(user);
		free(user);
		if (pw)
			return (ft_strdup(pw->pw_dir));
	}
	return (NULL);
}

int					ft_exp_tilde(t_txtlist *txt, t_42sh *shell)
{
	char			*res;

	if (txt->data[txt->start + txt->len]
		&& txt->data[txt->start + txt->len] != '/'
		&& txt->data[txt->start + txt->len] != ':')
		return (ft_exp_text(txt, shell));
	if (txt->len == 1)
		res = ft_tilde_alone(shell);
	else if (txt->data[txt->start + 1] == '+')
		res = ft_getvar("PWD", shell);
	else if (txt->data[txt->start + 1] == '-')
		res = ft_getvar("OLDPWD", shell);
	else
		res = ft_tilde_user(txt);
	if (!res)
		return (ft_exp_text(txt, shell));
	txt->data = res;
	return (0);
}
