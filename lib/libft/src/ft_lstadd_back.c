/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armandanger <armandanger@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:32:54 by aranger           #+#    #+#             */
/*   Updated: 2023/12/31 17:14:54 by armandanger      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	struct s_list	*a;

	if (new)
	{
		a = ft_lstlast(*lst);
		if (a != 0)
		{
			a->next = new;
			new->prev = a;
		}
		else
			*lst = new;
	}
}
