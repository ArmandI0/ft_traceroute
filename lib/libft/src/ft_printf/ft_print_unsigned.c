/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:40:11 by aranger           #+#    #+#             */
/*   Updated: 2023/11/19 19:41:01 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_base_unsigned(unsigned int nbr, char *radix)
{
	unsigned int		modulo;
	unsigned int		base;

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
			ft_putnbr_base_unsigned(nbr, radix);
			ft_putchar_fd(radix[modulo], 1);
		}
	}
}

static int	ft_size_unsigned(unsigned int n, int base)
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

int	ft_print_unsigned(unsigned int nbr)
{
	ft_putnbr_base_unsigned(nbr, "0123456789");
	return (ft_size_unsigned(nbr, 10));
}

int	ft_print_hexadecimal_lower(unsigned int nbr)
{
	ft_putnbr_base_unsigned(nbr, "0123456789abcdef");
	return (ft_size_unsigned(nbr, 16));
}

int	ft_print_hexadecimal_upper(unsigned int nbr)
{
	ft_putnbr_base_unsigned(nbr, "0123456789ABCDEF");
	return (ft_size_unsigned(nbr, 16));
}
