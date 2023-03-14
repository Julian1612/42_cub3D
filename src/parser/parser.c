/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:14:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/14 21:34:06 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int	check_args(int *argc, char **argv);
static int	check_if_all_textures_init(t_map *map_data);
static int	check_mandatory_textures(t_map *map_data);
static int	check_bonus_textures(t_map *map_data);
static int	check_for_invalid_definitions(t_map *map_data);
static int	check_char(t_map *map_data, char character);

int	parser(int *argc, char **argv, t_map *map_data)
{
	if (check_args(argc, argv))
		return (1);
	if (check_file(argv[1], "cub"))
		return (1);
	if (get_file_data(map_data, argv[1]))
		return (1);
	if (check_map(map_data))
		return (1);
	if (check_mandatory_textures(map_data))
		return (1);
	if (check_bonus_textures(map_data))
		return (1);
	if (check_for_invalid_definitions(map_data))
		return (1);
	return (0);
}

static int	check_args(int *argc, char **argv)
{
	if (*argc != 2)
	{
		error_message(1);
		return (1);
	}
	if (argv[1][0] == '\0')
	{
		error_message(1);
		return (1);
	}
	return (0);
}

static int	check_mandatory_textures(t_map *map_data)
{
	if (map_data->north == NULL)
		return (error_textures(6));
	else if (map_data->south == NULL)
		return (error_textures(6));
	else if (map_data->west == NULL)
		return (error_textures(6));
	else if (map_data->east == NULL)
		return (error_textures(6));
	else if (map_data->floor_rgb_arr[0] == -1
		|| map_data->floor_rgb_arr[1] == -1
		|| map_data->floor_rgb_arr[2] == -1)
		return (error_textures(4));
	else if (map_data->ceiling_rgb_arr[0] == -1
		|| map_data->ceiling_rgb_arr[1] == -1
		|| map_data->ceiling_rgb_arr[2] == -1)
		return (error_textures(4));
	return (0);
}

static int	check_bonus_textures(t_map *map_data)
{
	int			i;
	int			j;

	i = 0;
	while (map_data->map[i] == NULL)
	{
		j = 0;
		while (map_data->map[i][j])
		{
			check_char(map_data, map_data->map[i][j]);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_char(t_map *map_data, char character)
{
	if (character == 'D')
	{
		if (map_data->door == NULL)
			return (error_textures(7));
	}
	else if (character == 'B')
	{
		if (map_data->barrel == NULL)
			return (error_textures(7));
	}
	else if (character == 'E')
	{
		if (map_data->enemy == NULL)
			return (error_textures(7));
	}
	return (0);
}

static int	check_for_invalid_definitions(t_map *map_data)
{
	int			i;
	int			j;

	i = 0;
	while (map_data->map[i] == NULL)
	{
		printf("hi\n");
		j = 0;
		while (map_data->map[i][j])
		{
			if (map_data->map[i][j] != '0' && map_data->map[i][j] != '1'
				&& map_data->map[i][j] != 'N' && map_data->map[i][j] != 'S'
				&& map_data->map[i][j] != 'W' && map_data->map[i][j] != 'E'
				&& map_data->map[i][j] != 'D' && map_data->map[i][j] != 'B'
				&& map_data->map[i][j] != 'E' && map_data->map[i][j] != ' ')
				return (error_get_map(5));
			j++;
		}
		i++;
	}
	return (0);
	return (0);
}
