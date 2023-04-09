/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:03:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/09 13:49:08 by jschneid         ###   ########.fr       */
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
	else if (error_code == 5)
		printf("Error!\nMultiple wall texture definitions\n");
	else if (error_code == 6)
		printf("Error!\nMultiple RGB definitions\n");
	else if (error_code == 7)
		printf("Error!\nMultiple bonus texture definitions\n");
	else if (error_code == 8)
		printf("Error!\nThere is no file path defined\n");
	else if (error_code == 9)
		printf("Error!\nFile has not data type png\n");
	else if (error_code == 10)
		printf("Error!\nCould't find file for wall texture\n");
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
		printf("Error!\nRGB definition is invalid\n");
	else if (error_code == 6)
	{
		printf("Error!\nFile path for wall texture is missing\n");
		printf("or on the wrong position\n");
	}
	else if (error_code == 7)
		printf("Error!\nFile path for bonus texture is missing\n");
	printf("========================================\n");
	free_struct(map_data);
	return (1);
}

int	error_textures_2(int error_code, t_map *map_data)
{
	printf("========================================\n");
	if (error_code == 1)
		printf("Error!\nInvalid Definition in .cub file\n");
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
		printf("Error!\nFile contains no map\n");
	else if (error_code == 5)
		printf("Error!\nInvalid character in map\n");
	else if (error_code == 4)
		printf("Error!\nNo starting position found\n");
	else if (error_code == 3)
		printf("Error!\nChill bro, this map is too big\n");
	else if (error_code == 6)
		printf("Error!\nMultiple player definiton\n");
	else if (error_code == 7)
		printf("Error!\nInvalid new line\n");
	else if (error_code == 8)
		printf("Error!\nPlayer is out of bounds\n");
	printf("========================================\n");
	free_struct(map_data);
	return (1);
}

static void	free_struct(t_map *map_data)
{
	int	i;

	if (map_data == NULL)
		return ;
	i = 0;
	while (i < 10)
	{
		if (map_data->objects[i].path != NULL)
			free(map_data->objects[i].path);
		i++;
	}
	i = 0;
	if (map_data->map != NULL)
	{
		while (map_data->map[i] != NULL)
		{
			free(map_data->map[i]);
			i++;
		}
		free(map_data->map);
	}
}
