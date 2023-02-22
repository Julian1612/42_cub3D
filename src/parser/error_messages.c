/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:03:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/22 15:06:09 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>

void	error_message(int error_code)
{
	if (error_code == 1)
		printf("Error!\nWrong amount of argument\n");
	else if (error_code == 2)
		printf("Error!\nFile not found\n");
	else if (error_code == 3)
		printf("Error!\nFile has wrong datatype\n");
	else if (error_code == 4)
		printf("Error!\nMalloc failed\n");
}
