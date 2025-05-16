/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fd_others.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:02:31 by aranger           #+#    #+#             */
/*   Updated: 2024/02/29 10:39:32 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

static int	ft_size_int(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	n = n / 10;
	i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

size_t	ft_print_char(char c, int fd)
{
	ft_putchar_fd(c, fd);
	return (1);
}

size_t	ft_print_string(char *str, int fd)
{
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	ft_putstr_fd(str, fd);
	return (ft_strlen(str));
}

int	ft_print_decimal(int nbr, int fd)
{
	ft_putnbr_fd(nbr, fd);
	return (ft_size_int(nbr));
}
