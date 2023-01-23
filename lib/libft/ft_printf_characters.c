/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_characters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:09:46 by jschneid          #+#    #+#             */
/*   Updated: 2022/08/16 17:22:38 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Gets the value from the argument and uses function 'put_char'
// to print it to the standart output
int	output_character(va_list arguments)
{
	int	character;

	character = va_arg(arguments, int);
	print_character(character);
	return (1);
}
