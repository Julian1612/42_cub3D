/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:10:15 by jschneid          #+#    #+#             */
/*   Updated: 2022/08/16 17:23:11 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Gets the pointer adress,
// gets the length of the adress with 'get_number_length'
// and prints it with the 'prints_ptr_address'
int	output_pointer_address(va_list arguments)
{
	int					length_address;
	unsigned long long	ptr;

	ptr = (unsigned long long) va_arg(arguments, void *);
	length_address = number_length_hexadecimal(ptr);
	write(1, "0x", 2);
	print_pointer_address(ptr);
	return (length_address + 2);
}

// prints the given pointer address as a lowercase hexadecimal number
// using the 'print_char' function
void	print_pointer_address(unsigned long long decimal_nbr)
{
	unsigned long long	new_value;

	new_value = decimal_nbr % 16 + 48;
	decimal_nbr /= 16;
	if (decimal_nbr > 0)
		print_pointer_address(decimal_nbr);
	if (new_value == 58)
		new_value = 'a';
	else if (new_value == 59)
		new_value = 'b';
	else if (new_value == 60)
		new_value = 'c';
	else if (new_value == 61)
		new_value = 'd';
	else if (new_value == 62)
		new_value = 'e';
	else if (new_value == 63)
		new_value = 'f';
	print_character(new_value);
}
