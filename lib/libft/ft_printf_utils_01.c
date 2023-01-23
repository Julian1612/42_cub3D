/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:14:06 by jschneid          #+#    #+#             */
/*   Updated: 2022/08/16 17:29:21 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Gets the length of the given decimal number
long	number_length(long number)
{
	int	index;

	index = 0;
	if (number == 0 || number < 0)
		index++;
	while (number != 0)
	{
		number /= 10;
		index++;
	}
	return (index);
}

// Gets the length of the given hexadecimal number
int	number_length_hexadecimal(unsigned long long number)
{
	int	index;

	index = 0;
	if (number == 0 || number < 0)
		index++;
	while (number != 0)
	{
		number /= 16;
		index++;
	}
	return (index);
}

// Converts the given long number to a string
char	*get_string(long number, char *string, long length_number)
{
	long long	new_number;
	int			sign;

	new_number = 0;
	sign = 0;
	string[length_number] = '\0';
	if (number == 0)
		string[0] = '0';
	if (number < 0)
	{
		number *= -1;
		sign = 1;
	}
	while (length_number > 0)
	{
		new_number = number % 10;
		string[length_number -1] = 48 + new_number;
		number /= 10;
		length_number--;
	}
	if (sign == 1)
		string[0] = '-';
	return (string);
}
