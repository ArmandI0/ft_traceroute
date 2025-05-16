/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:27:35 by aranger           #+#    #+#             */
/*   Updated: 2023/11/02 16:12:09 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_rev_char_tab(char *tab, int size)
{
	int		i;
	int		j;
	char	tmp;

	j = size - 1;
	i = 0;
	while (i < size / 2)
	{
		tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;
		i++;
		j--;
	}
	return (tab);
}

static int	ft_nbsize(int n)
{
	int	i;
	int	value;

	i = 0;
	if (n < 0)
		i++;
	value = n / 10;
	i++;
	while (value != 0)
	{
		value = value / 10;
		i++;
	}
	return (i);
}

static char	*ft_int_min(char *dst)
{
	ft_strlcpy(dst, "-2147483648", 12);
	return (dst);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		size;

	size = ft_nbsize(n);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	if (n == -2147483648)
		return (ft_int_min(str));
	i = 0;
	str[size] = '\0';
	if (n < 0)
	{
		n = n * -1;
		str[size - 1] = '-';
	}
	while (n >= 10)
	{
		str[i] = '0' + (n % 10);
		n = n / 10;
		i++;
	}
	str[i] = '0' + n;
	return (ft_rev_char_tab(str, size));
}
