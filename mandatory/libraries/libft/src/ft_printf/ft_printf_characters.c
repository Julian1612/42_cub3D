/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_characters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:09:46 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/08 12:09:33 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Gets the value from the argument and uses function 'put_char'
// to print it to the standart output
int	output_character(va_list arguments)
{
	int	character;

	character = va_arg(arguments, int);
	print_character(character);
	return (1);
}
