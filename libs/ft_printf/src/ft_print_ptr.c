/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:38:29 by zpalfi            #+#    #+#             */
/*   Updated: 2022/02/07 17:14:44 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_ptr_2(uintptr_t n)
{
	if (n >= 16)
	{
		ft_print_ptr_2(n / 16);
		ft_print_ptr_2(n % 16);
	}
	else
	{
		if (n <= 9)
			ft_print_char((n + '0'));
		else
			ft_print_char((n - 10 + 'a'));
	}
}

static int	ft_len_ptr(uintptr_t n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

int	ft_print_ptr(unsigned long long n)
{
	int	len;

	len = 0;
	len += write(1, "0x", 2);
	if (n == 0)
		len += write(1, "0", 1);
	else
	{
		ft_print_ptr_2(n);
		len += ft_len_ptr(n);
	}
	return (len);
}
