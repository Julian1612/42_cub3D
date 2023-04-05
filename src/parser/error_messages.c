/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:03:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/05 10:52:53 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>

static void	free_struct(t_map *map_data);

int	error_message(int error_code, t_map *map_data)
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
	free_struct(map_data);
	return (1);
}

int	error_textures(int error_code, t_map *map_data)
{
	printf("========================================\n");
	if (error_code == 1)
		printf("Error!\nFailed getting path of texture\n");
	else if (error_code == 2)
		printf("Error!\nFile is empty\n");
	else if (error_code == 3)
		printf("Error!\nFilepath to .png file is missing\n");
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
	else if (error_code == 8)
		printf("Error!\nFile has not datatype png\n");
	printf("========================================\n");
	free_struct(map_data);
	return (1);
}

int	error_get_map(int error_code, t_map *map_data)
{
	printf("========================================\n");
	if (error_code == 1)
		printf("Error!\nMap is invalid\n");
	else if (error_code == 2)
		printf("Error!\nfile contains no map\n");
	else if (error_code == 5)
		printf("Error!\nInvalid character in map\n");
	else if (error_code == 4)
		printf("Error!\nNo starting position found\n");
	else if (error_code == 3)
		printf("Error!\nChill bro, this map is too big\n");
	else if (error_code == 6)
		printf("Error!\nMultiple player definiton\n");
	printf("========================================\n");
	free_struct(map_data);
	return (1);
}

static void	free_struct(t_map *map_data)
{
	if (map_data == NULL)
		return ;
	if (map_data->map != NULL)
		ft_free_arr((void **)map_data->map);
}
