/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:53:36 by zpalfi            #+#    #+#             */
/*   Updated: 2022/01/31 16:39:23 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

int		ft_printf(const char *s, ...);
int		ft_print_str(char *s);
int		ft_print_ptr(unsigned long long n);
int		ft_print_format(va_list argptr, char c);
int		ft_print_char(char c);
int		ft_print_n(int nbr);
int		ft_print_un(unsigned int nbr);
int		ft_print_x(unsigned int n);
int		ft_print_x2(unsigned int n);

#endif