/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:59:49 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/17 18:19:14 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1);

char	*ft_strdup(const char *s1)
{
	int		len;
	void	*str;

	len = ft_strlen(s1) + 1;
	str = malloc(len * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, len);
	return (str);
}
