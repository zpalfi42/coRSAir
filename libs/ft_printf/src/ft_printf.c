/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:53:58 by zpalfi            #+#    #+#             */
/*   Updated: 2022/03/14 14:20:51 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		ft_print_str("(null)");
		return (6);
	}
	while (s[i])
	{
		ft_print_char(s[i]);
		i++;
	}
	return (i);
}

int	ft_print_format(va_list argptr, char c)
{
	int	len;

	len = 0;
	if (c == '%')
		len += ft_print_char('%');
	else if (c == 'c')
		len += ft_print_char(va_arg(argptr, int));
	else if (c == 's')
		len += ft_print_str(va_arg(argptr, char *));
	else if (c == 'p')
		len += ft_print_ptr(va_arg(argptr, unsigned long long));
	else if (c == 'd')
		len += ft_print_n(va_arg(argptr, int));
	else if (c == 'i')
		len += ft_print_n(va_arg(argptr, int));
	else if (c == 'u')
		len += ft_print_un(va_arg(argptr, unsigned int));
	else if (c == 'x')
		len += ft_print_x(va_arg(argptr, unsigned int));
	else if (c == 'X')
		len += ft_print_x2(va_arg(argptr, unsigned int));
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	argptr;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(argptr, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_print_format(argptr, str[i + 1]);
			i++;
		}
		else
			len += ft_print_char(str[i]);
		i++;
	}
	va_end(argptr);
	return (len);
}
