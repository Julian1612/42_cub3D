/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 08:31:15 by jschneid          #+#    #+#             */
/*   Updated: 2022/04/22 15:30:54 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t size);

char	*ft_strnstr(const char *haystack, const char *needle, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	diff;

	i = 0;
	if (*needle == '\0' || needle == NULL)
		return ((char *) haystack);
	while (haystack[i] != '\0')
	{
		j = 0;
		diff = 0;
		while (haystack[i + j] != '\0' && needle[j] != '\0' && (i + j) < size)
		{
			diff = haystack[i + j] - needle[j];
			if (diff != 0)
				break ;
			j++;
		}
		if (diff == 0 && needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}
