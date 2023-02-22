/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:56:49 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/08 12:08:55 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// The printf utility formats and prints its arguments, after the first,
// under control of the format.  The format is a character string which
// contains three types of objects: plain characters, which are simply copied to
// standard output, character escape sequences which are converted and copied
// to the standard output and format specifications,
// each of which causes printing of the next successive argument.
int	ft_printf(const char *input_str, ...)
{
	int		printed_chars;
	va_list	arguments;

	printed_chars = 0;
	va_start(arguments, input_str);
	printed_chars = write_string(input_str, arguments);
	va_end(arguments);
	return (printed_chars);
}
