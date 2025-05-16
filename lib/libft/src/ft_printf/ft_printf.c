/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:36:03 by aranger           #+#    #+#             */
/*   Updated: 2023/11/19 19:41:21 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_param(char c, va_list ap)
{
	int	nb;

	nb = 0;
	if (c == 'c')
		nb = ft_print_char((va_arg(ap, int)));
	if (c == 's')
		nb = ft_print_string(va_arg(ap, char *));
	if (c == 'p')
		nb = ft_print_adress(va_arg(ap, unsigned long long));
	if (c == 'd' || c == 'i')
		nb = ft_print_decimal(va_arg(ap, int));
	if (c == 'u')
		nb = ft_print_unsigned(va_arg(ap, unsigned int));
	if (c == 'x')
		nb = ft_print_hexadecimal_lower(va_arg(ap, unsigned int));
	if (c == 'X')
		nb = ft_print_hexadecimal_upper(va_arg(ap, unsigned int));
	if (c == '%')
		nb = ft_print_char(c);
	return (nb);
}

int	ft_printf(const char *str, ...)
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
			size += ft_param(str[i + 1], ap);
			i++;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			size++;
		}
		i++;
	}
	va_end(ap);
	return (size);
}
