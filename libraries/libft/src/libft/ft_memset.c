/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:53:05 by jschneid          #+#    #+#             */
/*   Updated: 2022/04/13 08:44:37 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len);

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned long	i;
	char			*str;

	i = 0;
	str = (char *) b;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (str);
}
