/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:15:28 by aranger           #+#    #+#             */
/*   Updated: 2023/11/06 11:15:29 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	struct s_list	*ptr;

	if (lst)
	{
		ptr = lst;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		return (ptr);
	}
	return (NULL);
}
