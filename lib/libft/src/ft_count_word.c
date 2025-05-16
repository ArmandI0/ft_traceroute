/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:59:51 by aranger           #+#    #+#             */
/*   Updated: 2023/12/26 17:34:58 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_word(char *line)
{
	int	i;
	int	a;
	int	count;

	i = 0;
	a = 0;
	count = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]) == 1)
			a = 0;
		if (ft_isspace(line[i]) == 0 && a != 1)
		{
			count++;
			a = 1;
		}
		i++;
	}
	return (count);
}
