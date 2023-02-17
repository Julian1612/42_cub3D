/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:03:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/17 13:29:09 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
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
	else if (error_code == 5)
		printf("Error!\nMultiple texture definitions\n");
	else if (error_code == 6)
		printf("Error!\nMap is not surrunded by walls\n");
	else if (error_code == 7)
		printf("Error!\nFailed getting path of texture\n");
	else if (error_code == 8)
		printf("Error!\nFile is empty\n");
	else if (error_code == 9)
		printf("Error!\nfile contains no map\n");
	else if (error_code == 10)
		printf("Error!\nFilepath to .xpm file is missing\n");
	else if (error_code == 11)
		printf("Error!\nRGB values for floor are missing\n");
	else if (error_code == 12)
		printf("Error!\nRGB values for ceiling are missing\n");
	else if (error_code == 13)
		printf("Error!\nMap is in incorrect position. Please place the map under the texture declarations\n");
	else if (error_code == 14)
		printf("Error!\nThere are colors values for the RGBs missing\n");
	else if (error_code == 15)
		printf("Error!\nEmty line in map\n");
	else if (error_code == 16)
		printf("Error!\nInvalid character in map\n");
}
