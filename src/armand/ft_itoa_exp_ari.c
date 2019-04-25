/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_exp_ari.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 17:29:24 by achavy            #+#    #+#             */
/*   Updated: 2019/04/25 05:03:03 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_put_spaces(char *str, int i, int n)
{
	i++;
	while (i < n)
	{
		str[i] = ' ';
		i++;
	}
}

void	ft_itoa_exp_ari(char *str, int nbr, int n)
{
	unsigned int	nb;
	int				i;
	int				div;

	i = 0;
	div = 1000000000;
	if (nbr < 0)
	{
		str[i] = '-';
		i++;
		nb = -nbr;
	}
	else
		nb = nbr;
	while (div != 1 && nb / div == 0)
		div = div / 10;
	while (div != 1)
	{
		str[i] = nb / div + 48;
		i++;
		nb = nb % div;
		div = div / 10;
	}
	str[i] = nb + 48;
	ft_put_spaces(str, i, n);
}
