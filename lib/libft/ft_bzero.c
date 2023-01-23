/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:07:21 by jschneid          #+#    #+#             */
/*   Updated: 2022/04/13 08:43:25 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n);

void	ft_bzero(void *s, size_t n)
{
	char				*c;
	unsigned long		i;
	int					j;

	c = s;
	i = 0;
	j = n;
	while (i < n)
	{
		c[i] = '\0';
		i++;
	}
}
