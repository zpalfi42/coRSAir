/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:11:04 by zpalfi            #+#    #+#             */
/*   Updated: 2022/01/31 17:23:19 by zpalfi           ###   ########.fr       */
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
		write(1, &"0123456789abcdef"[n % 16], 1);
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

int	ft_print_x(unsigned int n)
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
