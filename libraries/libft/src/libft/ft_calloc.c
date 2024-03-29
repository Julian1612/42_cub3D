/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:08:57 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/10 17:34:31 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size);

void	*ft_calloc(size_t count, size_t size)
{
	void	*rtn;

	if (size > 0 && (SIZE_MAX / size) < count)
		return (NULL);
	rtn = malloc(count * size);
	if (rtn == NULL)
		return (NULL);
	ft_memset(rtn, '\0', (count * size));
	return (rtn);
}
