/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_adress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:40:01 by aranger           #+#    #+#             */
/*   Updated: 2023/11/19 19:41:59 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base_adress(unsigned long long nbr, char *radix)
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
			ft_putchar_fd(radix[modulo], 1);
		}
		else
		{
			ft_putnbr_base_adress(nbr, radix);
			ft_putchar_fd(radix[modulo], 1);
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

int	ft_print_adress(unsigned long long ptr)
{
	if (ptr > 0)
	{
		write(1, "0x", 2);
		ft_putnbr_base_adress(ptr, "0123456789abcdef");
		return (ft_adress_size(ptr, 16) + 2);
	}
	else
	{
		write(1, "(nil)", 5);
		return (5);
	}
}
