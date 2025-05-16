/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fd_adress.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:40:01 by aranger           #+#    #+#             */
/*   Updated: 2024/02/29 10:46:09 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

void	ft_putnbr_base_adress(unsigned long long nbr, char *radix, int fd)
{
	int		modulo;
	int		base;

	if (radix)
	{
		base = ft_strlen(radix);
		modulo = nbr % base;
		nbr = nbr / base;
		if (nbr == 0)
		{
			ft_putchar_fd(radix[modulo], fd);
		}
		else
		{
			ft_putnbr_base_adress(nbr, radix, fd);
			ft_putchar_fd(radix[modulo], fd);
		}
	}
}

static int	ft_adress_size(unsigned long long n, int base)
{
	int	i;

	i = 0;
	n = n / base;
	i++;
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

int	ft_print_adress(unsigned long long ptr, int fd)
{
	if (ptr > 0)
	{
		write(1, "0x", 2);
		ft_putnbr_base_adress(ptr, "0123456789abcdef", fd);
		return (ft_adress_size(ptr, 16) + 2);
	}
	else
	{
		write(1, "(nil)", 5);
		return (5);
	}
}
