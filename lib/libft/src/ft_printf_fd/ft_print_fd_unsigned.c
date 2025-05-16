/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fd_unsigned.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:40:11 by aranger           #+#    #+#             */
/*   Updated: 2024/02/29 10:42:38 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

static void	ft_putnbr_base_unsigned(unsigned int nbr, char *radix, int fd)
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
			ft_putchar_fd(radix[modulo], fd);
		}
		else
		{
			ft_putnbr_base_unsigned(nbr, radix, fd);
			ft_putchar_fd(radix[modulo], fd);
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

int	ft_print_unsigned(unsigned int nbr, int fd)
{
	ft_putnbr_base_unsigned(nbr, "0123456789", fd);
	return (ft_size_unsigned(nbr, 10));
}

int	ft_print_hexadecimal_lower(unsigned int nbr, int fd)
{
	ft_putnbr_base_unsigned(nbr, "0123456789abcdef", fd);
	return (ft_size_unsigned(nbr, 16));
}

int	ft_print_hexadecimal_upper(unsigned int nbr, int fd)
{
	ft_putnbr_base_unsigned(nbr, "0123456789ABCDEF", fd);
	return (ft_size_unsigned(nbr, 16));
}
