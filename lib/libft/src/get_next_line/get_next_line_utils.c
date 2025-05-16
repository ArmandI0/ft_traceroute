/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:59:32 by aranger           #+#    #+#             */
/*   Updated: 2024/01/11 13:36:01 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	free(s1);
	free(s2);
	return (str);
}

void	*ft_calloc_gnl(size_t nmemb, size_t size)
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

char	*ft_strrchr_gnl(const char *s, int c)
{
	size_t		i;
	const char	*tmp;

	tmp = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			tmp = &s[i];
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return ((char *)tmp);
}
