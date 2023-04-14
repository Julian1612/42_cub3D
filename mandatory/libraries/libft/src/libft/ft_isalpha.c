/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:10:41 by jschneid          #+#    #+#             */
/*   Updated: 2022/04/13 08:43:44 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int i);

int	ft_isalpha(int i)
{
	if (i >= 'a' && i <= 'z')
		return (1);
	else if (i >= 'A' && i <= 'Z')
		return (1);
	else
		return (0);
}
