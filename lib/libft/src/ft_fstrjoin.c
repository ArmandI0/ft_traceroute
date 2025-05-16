/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fstrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:28:51 by nledent           #+#    #+#             */
/*   Updated: 2023/12/31 17:49:35 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_fstrjoin(char const *s1, char const *s2)
{
	char	*strcat;
	int		i;
	int		j;

	i = 0;
	strcat = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	strcat = ft_calloc(1, sizeof (char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (strcat == NULL)
		return (0);
	while (s1[i] != 0)
	{
		strcat[i] = s1[i];
		i++;
	}
	j = i;
	while (s2[i - j] != 0)
	{
		strcat[i] = s2[i - j];
		i++;
	}
	free ((char *)s1);
	free ((char *)s2);
	return (strcat);
}
