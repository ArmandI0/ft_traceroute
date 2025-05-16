/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:36:03 by aranger           #+#    #+#             */
/*   Updated: 2024/02/29 10:51:23 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

static int	ft_param(char c, va_list ap, int fd)
{
	int	nb;

	nb = 0;
	if (c == 'c')
		nb = ft_print_char((va_arg(ap, int)), fd);
	if (c == 's')
		nb = ft_print_string(va_arg(ap, char *), fd);
	if (c == 'p')
		nb = ft_print_adress(va_arg(ap, unsigned long long), fd);
	if (c == 'd' || c == 'i')
		nb = ft_print_decimal(va_arg(ap, int), fd);
	if (c == 'u')
		nb = ft_print_unsigned(va_arg(ap, unsigned int), fd);
	if (c == 'x')
		nb = ft_print_hexadecimal_lower(va_arg(ap, unsigned int), fd);
	if (c == 'X')
		nb = ft_print_hexadecimal_upper(va_arg(ap, unsigned int), fd);
	if (c == '%')
		nb = ft_print_char(c, fd);
	return (nb);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	ap;
	int		i;
	int		size;

	i = 0;
	size = 0;
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			size += ft_param(str[i + 1], ap, fd);
			i++;
		}
		else
		{
			ft_putchar_fd(str[i], fd);
			size++;
		}
		i++;
	}
	va_end(ap);
	return (size);
}
