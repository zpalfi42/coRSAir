/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_un.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:59:29 by zpalfi            #+#    #+#             */
/*   Updated: 2022/01/31 16:26:03 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_ifpositive(unsigned int nbr)
{
	unsigned int	aux;
	unsigned int	n;

	aux = nbr / 10;
	n = nbr % 10;
	ft_print_n(aux);
	ft_print_char(n + '0');
}

static int	ft_un_len(unsigned int nbr)
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

int	ft_print_un(unsigned int nbr)
{
	unsigned int	len;

	len = ft_un_len(nbr);
	if (nbr >= 10)
		ft_ifpositive(nbr);
	else
		ft_print_char(nbr + '0');
	return (len);
}
