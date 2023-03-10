/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:10:24 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/08 12:09:16 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Gets the value from the argument, itarrets through the string and prints
// every character with help of 'print_char' function
int	output_string(va_list arguments)
{
	int		index;
	char	*string;

	index = 0;
	string = va_arg(arguments, char *);
	if (string == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (string[index] != '\0')
	{
		print_character(string[index]);
		index++;
	}
	return (index);
}
