/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:06:22 by jschneid          #+#    #+#             */
/*   Updated: 2022/04/13 10:17:05 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len);
static void	fwd_cpy_str(char *des, const char *sou, size_t len);
static void	bck_cpy_str(char *des, const char *sou, size_t len);

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*des;
	const char		*sou;

	if (dst == src)
		return (dst);
	des = (char *) dst;
	sou = (const char *) src;
	if (!(sou < des && sou + len > des))
		fwd_cpy_str(des, sou, len);
	else
		bck_cpy_str(des, sou, len);
	return (dst);
}

static void	fwd_cpy_str(char *des, const char *sou, size_t len)
{
	unsigned long	i;

	i = 0;
	while (i < len)
	{
		des[i] = sou[i];
		i++;
	}
}

static void	bck_cpy_str(char *des, const char *sou, size_t len)
{
	while (len > 0)
	{
		des[len -1] = sou[len -1];
		len--;
	}
}
