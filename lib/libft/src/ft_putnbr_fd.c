/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:26:40 by aranger           #+#    #+#             */
/*   Updated: 2023/11/02 20:07:27 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_minus(int nb, int fd)
{
	if (nb < 0)
	{
		nb = nb / -1;
		write(fd, "-", 1);
	}
	return (nb);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	tmp;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		n = ft_print_minus(n, fd);
		if (n > -10 && n < 10)
			ft_putchar_fd('0' + n, fd);
		else
		{
			tmp = n % 10;
			n = n / 10;
			if (n >= 10)
			{
				ft_putnbr_fd(n, fd);
				ft_putchar_fd('0' + tmp, fd);
			}
			else
			{
				ft_putchar_fd('0' + n, fd);
				ft_putchar_fd('0' + tmp, fd);
			}
		}
	}
}
