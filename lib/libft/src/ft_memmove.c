/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:34:31 by aranger           #+#    #+#             */
/*   Updated: 2023/11/03 12:40:58 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	size_t			i;

	i = 0;
	if (src == NULL && dest == NULL)
		return (NULL);
	if ((unsigned char *)dest > (unsigned char *)src)
	{
		while (i < size)
		{
			((unsigned char *)dest)[size - 1] = ((unsigned char *)src)[size -1];
			size--;
		}
	}
	else
	{
		while (i < size)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}
