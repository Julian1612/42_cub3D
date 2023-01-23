/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_00.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:35:17 by jschneid          #+#    #+#             */
/*   Updated: 2022/08/16 17:23:23 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Iterrats through the given string and prints the single charcters.
// When there is a '%' character the function starts function 'conversion_check'
int	write_string(const char *input_str, va_list arguments)
{
	int		index;
	int		char_counter;

	index = 0;
	char_counter = 0;
	while (input_str[index] != '\0')
	{
		if (input_str[index] == '%' && (input_str[index + 1] == '%'
				|| input_str[index + 1] == 'c' || input_str[index + 1] == 's'
				|| input_str[index + 1] == 'p' || input_str[index + 1] == 'i'
				|| input_str[index + 1] == 'd' || input_str[index + 1] == 'u'
				|| input_str[index + 1] == 'x' || input_str[index + 1] == 'X'))
		{
			char_counter += variable_check(input_str, index, arguments);
			index++;
		}
		else
		{
			print_character(input_str[index]);
			char_counter++;
		}
		index++;
	}
	return (char_counter);
}

// Checks wich character is used after the %
// and starts the function wich is used for that case.
// after the called function is finished it returns the number of printed
// characters to the 'conversion_check' function and the
// 'conversion_check' function  return the value.
int	variable_check(const char *input_str, int index, va_list arguments)
{
	if (input_str[index + 1] == 'c')
		return (output_character(arguments));
	else if (input_str[index + 1] == 's')
		return (output_string(arguments));
	else if (input_str[index + 1] == 'p')
		return (output_pointer_address(arguments));
	else if (input_str[index + 1] == 'd')
		return (output_numbers(arguments));
	else if (input_str[index + 1] == 'i')
		return (output_numbers(arguments));
	else if (input_str[index + 1] == 'u')
		return (output_unsigned_integer(arguments));
	else if (input_str[index + 1] == 'x')
		return (output_lowercase_hexadecimal(arguments));
	else if (input_str[index + 1] == 'X')
		return (output_uppercase_hexadecimal(arguments));
	else if (input_str[index + 1] == '%')
		return (output_percent());
	return (0);
}

// Counts the digits of the given number
int	get_number_length(long long ptr_address)
{
	int	length;

	length = 0;
	while (ptr_address > 0)
	{
		ptr_address /= 10;
		if (ptr_address > 0)
			length ++;
	}
	return (length);
}

// Writes the given character to the standart output
void	print_character(const char output_char)
{
	write(1, &output_char, 1);
}
