/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:56:49 by jschneid          #+#    #+#             */
/*   Updated: 2022/08/16 17:23:33 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
