/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:08:32 by jschneid          #+#    #+#             */
/*   Updated: 2022/08/16 17:23:07 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Gives the 'print_char' function a '%' prints it to the
// standart output and returns 1
int	output_percent(void)
{
	print_character('%');
	return (1);
}
