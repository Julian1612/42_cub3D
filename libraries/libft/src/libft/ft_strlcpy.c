/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:15:02 by jschneid          #+#    #+#             */
/*   Updated: 2022/04/22 14:24:21 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t destsize);

size_t	ft_strlcpy(char *dst, const char *src, size_t destsize)
{
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	while (src[c] != '\0')
		c++;
	if (destsize > 1)
	{
		while (i < destsize - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
	}
	if (i < destsize)
		dst[i] = '\0';
	return (c);
}
