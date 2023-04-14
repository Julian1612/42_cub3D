/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:49:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/14 05:45:04 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include "../types.h" // texture enum
#include "private_parser.h"
#include "../../libraries/libft/src/get_next_line/get_next_line.h" // gnl
#include <fcntl.h> // open
#include <unistd.h> // close
#include <stdio.h> // printf

int	check_textures_file(t_map *map_data, char *cub_file_path, char *data_type)
{
	int	fd;

	if (check_data_type(cub_file_path, data_type))
		return (error_message(9, map_data));
	fd = open(cub_file_path, O_RDONLY);
	if (fd < 0)
		return (error_message(10, map_data));
	close(fd);
	return (0);
}

int	check_mandatory_textures(t_map *map_data)
{
	int	i;

	i = 0;
	while (i <= WALL_WEST)
	{
		if (map_data->textures[i].path == NULL)
			return (error_textures(6, map_data));
		else if (check_textures_file(map_data,
				map_data->textures[i].path, "png"))
			return (1);
		i++;
	}
	if ((int)map_data->floor_color == -1)
		return (error_textures(WALL_WEST + 1, map_data));
	else if ((int)map_data->ceiling_color == -1)
		return (error_textures(4, map_data));
	return (0);
}

int	check_bonus_textures(t_map *map_data)
{
	int		fd_path;
	char	*path;
	int		i;

	fd_path = open("./textures/paths.txt", O_RDONLY);
	if (fd_path < 0)
		return (error_textures(7, map_data));
	i = WALL_WEST + 1;
	while (i < LAST)
	{
		path = get_next_line(fd_path);
		if (path == NULL)
			return (1);
		remove_last_char(path);
		map_data->textures[i].path = path;
		i++;
	}
	get_next_line(-1);
	return (0);
}
