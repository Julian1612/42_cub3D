/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:00:49 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/02 14:01:29 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arrlen(char **arr)
{
	int	i;

	if (!arr)
		return (-1);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}
