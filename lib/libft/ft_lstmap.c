/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:23:19 by jschneid          #+#    #+#             */
/*   Updated: 2022/04/25 09:38:30 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *node;

	if (lst != NULL)
	{
		while (lst != NULL)
		{
			node = ft_lstnew(f(lst->content));
			if (node != NULL)
			{

			}
			lst = lst->next;
		}
	}

}
