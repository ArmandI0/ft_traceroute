/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:09:05 by aranger           #+#    #+#             */
/*   Updated: 2023/11/02 19:28:37 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptn;
	size_t			i;
	size_t			a;

	i = 0;
	a = nmemb * size;
	if (a && a / size != nmemb)
		return (NULL);
	ptn = malloc(size * nmemb);
	if (ptn == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		ptn[i] = '\0';
		i++;
	}
	return ((void *)ptn);
}
