/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:35:29 by jschneid          #+#    #+#             */
/*   Updated: 2022/04/13 08:45:28 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	des_len;
	size_t	sou_len;
	size_t	len;
	size_t	i;

	des_len = ft_strlen(dst);
	sou_len = ft_strlen(src);
	i = 0;
	if (size > des_len)
		len = sou_len + des_len;
	else
		return (sou_len + size);
	while (des_len < size - 1 && src[i] != '\0')
	{
		dst[des_len] = src[i];
		des_len++;
		i++;
	}
	dst[des_len] = '\0';
	return (len);
}
