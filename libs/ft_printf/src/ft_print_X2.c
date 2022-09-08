/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_X2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:27:50 by zpalfi            #+#    #+#             */
/*   Updated: 2022/01/31 17:51:48 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_hex(unsigned int n)
{
	if (n >= 16)
	{
		ft_print_hex(n / 16);
		ft_print_hex(n % 16);
	}
	else
		write(1, &"0123456789ABCDEF"[n % 16], 1);
}

static int	ft_hex_len(unsigned int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

int	ft_print_x2(unsigned int n)
{
	int	count;

	count = ft_hex_len(n);
	if (n == 0)
	{
		write(1, "0", 1);
		count++;
	}
	else
		ft_print_hex(n);
	return (count);
}
