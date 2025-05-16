/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:15:01 by aranger           #+#    #+#             */
/*   Updated: 2023/12/04 11:44:13 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_split(char	const *s, char c)
{
	int	i;
	int	j;
	int	a;

	i = 0;
	j = 0;
	a = 0;
	while (s[i])
	{
		if (s[i] != c && a == 0)
		{
			j++;
			a = 1;
		}
		else if (s[i] == c)
			a = 0;
		i++;
	}
	return (j);
}

static char	*ft_add_word(char const *src, char c)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (src[j] && src[j] != c)
		j++;
	str = malloc(sizeof(char) * (j + 1));
	if (str == NULL)
		return (NULL);
	while (src[i] != c && src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	ft_free_all(char **tab, int size)
{
	while (size != 0)
	{
		free(tab[size]);
		size--;
	}
	free(tab[size]);
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	char	**tab;

	k = 0;
	i = 0;
	if (!s)
		return (NULL);
	tab = ft_calloc((ft_count_split(s, c) + 1), sizeof(char *));
	if (tab == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && s[i] && (i == 0 || s[i - 1] == c))
		{
			tab[k] = ft_add_word(&s[i], c);
			if (tab[k] == NULL)
				ft_free_all(tab, k);
			if (tab[k] == NULL)
				return (NULL);
			k++;
		}
		i++;
	}
	return (tab);
}
