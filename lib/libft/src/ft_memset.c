/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:23:40 by aranger           #+#    #+#             */
/*   Updated: 2023/11/02 19:25:55 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp;
	size_t			a;
	size_t			i;

	tmp = (unsigned char *) s;
	i = 0;
	a = c;
	while (i < n)
	{
		tmp[i] = a;
		i++;
	}
	return (s);
}
