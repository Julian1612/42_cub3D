/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:23:19 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/14 19:42:51 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;

	node = NULL;
	if (lst != NULL)
	{
		while (lst != NULL)
		{
			node = ft_lstnew(f(lst->content));
			if (node != NULL)
				ft_lstdelone(lst, del);
			lst = lst->next;
		}
	}
	return (node);
}
