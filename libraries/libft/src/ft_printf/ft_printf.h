/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:26:10 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/08 14:52:44 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "../libft/libft.h"

int			ft_printf(const char *input_str, ...);
// char		*ft_itoa(long n);
void		print_character(const char output_char);
int			write_string(const char *input_str, va_list arguments);
int			variable_check(const char *input_str,
				int index, va_list arguments);
int			output_character(va_list arguments);
int			output_string(va_list arguments);
int			output_numbers(va_list arguments);
int			output_integer(va_list arguments);//
int			output_percent(void);
int			output_pointer_address(va_list arguments);
void		print_pointer_address(unsigned long long decimal_nbr);
int			output_lowercase_hexadecimal(va_list argument);
void		print_lowercase_hexadecimal(unsigned int decimal_nbr);
int			output_uppercase_hexadecimal(va_list arguments);
void		print_uppercase_hexadecimal(unsigned int decimal_nbr);
int			output_unsigned_integer(va_list arguments);//
int			number_length_hexadecimal(unsigned long long numb);
long		number_length(long numb);
char		*get_string(long numb, char *str, long numb_len);

#endif
