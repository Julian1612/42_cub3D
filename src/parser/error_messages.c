/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:03:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/12 10:59:16 by jschneid         ###   ########.fr       */
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

void	error_textures(int error_code)
{
	if (error_code == 4)
		printf("Error!\nMalloc failed\n");
	else if (error_code == 5)
		printf("Error!\nMultiple texture definitions\n");
	else if (error_code == 7)
		printf("Error!\nFailed getting path of texture\n");
	else if (error_code == 8)
		printf("Error!\nFile is empty\n");
	else if (error_code == 10)
		printf("Error!\nFilepath to .xpm file is missing\n");
	else if (error_code == 14)
		printf("Error!\nThe values for the RGBs are missing\n");
	else if (error_code == 17)
		printf("Error!\nRGB value out of range\n");
}

void	error_get_map(int error_code)
{
	if (error_code == 1)
		printf("Error!\nWrong amount of argument\n");
	else if (error_code == 4)
		printf("Error!\nMalloc failed\n");
	else if (error_code == 6)
		printf("Error!\nMap is not surrounded by walls\n");
	else if (error_code == 9)
		printf("Error!\nfile contains no map\n");
	else if (error_code == 13)
	{
		printf("Error!\nMap is in incorrect position. ");
		printf("Please place the map under the texture declarations\n");
	}
	else if (error_code == 15)
		printf("Error!\nEmpty line in map\n");
	else if (error_code == 16)
		printf("Error!\nInvalid character in map\n");
}
