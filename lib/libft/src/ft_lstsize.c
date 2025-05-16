/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:45:45 by aranger           #+#    #+#             */
/*   Updated: 2023/11/06 10:45:48 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	struct s_list	*ptr;
	int				i;

	if (lst)
	{
		ptr = lst;
		i = 1;
		while (ptr->next != NULL)
		{
			i++;
			ptr = ptr->next;
		}
		return (i);
	}
	return (0);
}
