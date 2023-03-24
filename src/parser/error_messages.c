/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:03:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/24 10:35:30 by jschneid         ###   ########.fr       */
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
	return (ERROR);
}

int	error_textures(int error_code, t_map *map_data)
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
		printf("Error!\nFile path for bonus texture is missing or got wrong datatype\n");
	printf("========================================\n");
	free_struct(map_data);
	return (ERROR);
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
	printf("========================================\n");
	free_struct(map_data);
	return (ERROR);
}

static void	free_struct(t_map *map_data)
{
	if (map_data == NULL)
		return ;
	if (map_data->north.path != NULL)
		free(map_data->north.path);
	if (map_data->south.path != NULL)
		free(map_data->south.path);
	if (map_data->west.path != NULL)
		free(map_data->west.path);
	if (map_data->east.path != NULL)
		free(map_data->east.path);
	if (map_data->map != NULL)
		ft_free_arr((void **)map_data->map);
}
