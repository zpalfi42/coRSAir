/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:55:49 by zpalfi            #+#    #+#             */
/*   Updated: 2022/01/31 16:26:04 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static void	ft_ifpositive(int nbr)
{
	int	aux;
	int	n;

	aux = nbr / 10;
	n = nbr % 10;
	ft_print_n(aux);
	ft_print_char(n + '0');
}

static void	ft_ifnegative(int nbr)
{
	int	aux;
	int	n;

	aux = nbr / 10;
	n = (nbr * -1) % 10;
	ft_print_n(aux);
	ft_print_char(n + '0');
}

static int	ft_n_len(int nbr)
{
	int	count;

	if (nbr == 0)
		return (1);
	count = 0;
	if (nbr < 0)
		count++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		count++;
	}
	return (count);
}

int	ft_print_n(int nbr)
{
	int	aux;
	int	len;

	len = ft_n_len(nbr);
	if (nbr == -2147483648)
	{
		aux = -214748364;
		ft_print_n(aux);
		ft_print_char('8');
	}
	else if (nbr >= 10)
		ft_ifpositive(nbr);
	else if (nbr <= -10)
		ft_ifnegative(nbr);
	else if (nbr < 0)
	{
		ft_print_char('-');
		ft_print_char((nbr * -1) + '0');
	}
	else
		ft_print_char(nbr + '0');
	return (len);
}
