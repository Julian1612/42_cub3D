/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 08:42:01 by jschneid          #+#    #+#             */
/*   Updated: 2022/04/13 08:44:27 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n);

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long			i;
	char					*des;
	char const				*sou;

	i = 0;
	if (dst == src)
		return (dst);
	des = (char *) dst;
	sou = (const char *) src;
	while (i < n)
	{
		des[i] = sou[i];
		i ++;
	}
	return (des);
}
