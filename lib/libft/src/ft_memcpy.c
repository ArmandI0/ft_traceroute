/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:16:14 by aranger           #+#    #+#             */
/*   Updated: 2023/11/02 19:29:39 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned char	*source;
	unsigned char	*destination;
	size_t			i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	source = (unsigned char *) src;
	destination = (unsigned char *) dest;
	while (i < size)
	{
		destination[i] = source[i];
		i++;
	}
	return (destination);
}
