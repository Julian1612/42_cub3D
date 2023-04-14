/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:10:34 by jschneid          #+#    #+#             */
/*   Updated: 2022/04/13 08:43:39 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int i);

int	ft_isalnum(int i)
{
	if (i >= 'a' && i <= 'z')
		return (1);
	else if (i >= 'A' && i <= 'Z')
		return (1);
	else if (i >= '0' && i <= '9')
		return (1);
	else
		return (0);
}
