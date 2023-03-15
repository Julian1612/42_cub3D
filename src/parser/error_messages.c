/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:03:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/15 11:04:07 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>

int	error_message(int error_code)
{
	printf("========================================\n");
	if (error_code == 1)
		printf("Error!\nWrong amount of argument\n");
	else if (error_code == 2)
		printf("Error!\nFile not found\n");
	else if (error_code == 3)
		printf("Error!\nFile has wrong datatype\n");
	else if (error_code == 4)
		printf("Error!\nMalloc failed\n");
	printf("========================================\n");
	return (1);
}

int	error_textures(int error_code)
{
	printf("========================================\n");
	if (error_code == 1)
		printf("Error!\nFailed getting path of texture\n");
	else if (error_code == 2)
		printf("Error!\nFile is empty\n");
	else if (error_code == 3)
		printf("Error!\nFilepath to .xpm file is missing\n");
	else if (error_code == 4)
	{
		printf("Error!\nRGB codes missing\n");
		printf("or on the wrong position\n");
	}
	else if (error_code == 5)
		printf("Error!\nRGB value out of range\n");
	else if (error_code == 6)
	{
		printf("Error!\nFile path for wall texture is missing\n");
		printf("or on the wrong position\n");
	}
	else if (error_code == 7)
		printf("Error!\nFile path for bonus texture is missing\n");
	printf("========================================\n");
	return (1);
}

int	error_get_map(int error_code)
{
	printf("========================================\n");
	if (error_code == 1)
		printf("Error!\nMap is invalid\n");
	else if (error_code == 2)
		printf("Error!\nfile contains no map\n");
	// else if (error_code == 3)
	// {
	// 	printf("Error!\nMap is in incorrect position. ");
	// 	printf("Please place the map under the texture declarations\n");
	// }
	// else if (error_code == 4)
	// 	printf("Error!\nEmpty line in map\n");
	else if (error_code == 5)
		printf("Error!\nInvalid character in map\n");
	printf("========================================\n");
	return (1);
}
