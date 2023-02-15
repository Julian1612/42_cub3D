/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:03:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/15 18:19:24 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

void	error_message(int error_code)
{
	if (error_code == 1)
		printf("Error!\nWrong amount of arument\n");
	else if (error_code == 2)
		printf("Error!\nFile not found\n");
	else if (error_code == 3)
		printf("Error!\nFile has wrong datatype\n");
	else if (error_code == 4)
		printf("Error!\nMalloc failed\n");
	else if (error_code == 5)
		printf("Error!\nMultiple texture definitions\n");
	else if (error_code == 6)
		printf("Error!\nMap is not surrunded by walls\n");
	else if (error_code == 7)
		printf("Error!\nFailed getting path of texture\n");
	else if (error_code == 8)
		printf("Error!\nFile is emty\n");
	else if (error_code == 9)
		printf("Error!\nFile contains no map\n");
	else if (error_code == 10)
		printf("Error!\nNo file path for we\n");
}
