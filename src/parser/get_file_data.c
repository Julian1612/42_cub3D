/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:46:22 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/18 13:32:16 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdlib.h>
#include <stdio.h>

static int	read_map_data(t_map *map_data, int fd, int file_len);
static void	init_struct_null(t_map *map_data);
static int	get_file_len(char *path);
static int	check_line(t_map *map_data, char *line, int fd);

int	get_file_data(t_map *map_data, char *cub_file_path)
{
	int		file_len;
	int		fd;

	file_len = get_file_len(cub_file_path);
	if (file_len == 1)
		return (error_textures(2, map_data));
	fd = open(cub_file_path, O_RDONLY);
	if (fd == -1)
		return (error_message(2, map_data));
	init_struct_null(map_data);
	if (read_map_data(map_data, fd, file_len))
		return (1);
	close(fd);
	return (0);
}

static int	read_map_data(t_map *map_data, int fd, int file_len)
{
	int		i;
	char	*line;

	i = 0;
	while (i < file_len - 1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (1);
		if (check_line(map_data, line, fd))
		{
			free(line);
			break ;
		}
		free(line);
		i++;
	}
	return (0);
}

static void	init_struct_null(t_map *map_data)
{
	map_data->north = NULL;
	map_data->south = NULL;
	map_data->west = NULL;
	map_data->east = NULL;
	map_data->floor_rgb_arr[0] = -1;
	map_data->floor_rgb_arr[1] = -1;
	map_data->floor_rgb_arr[2] = -1;
	map_data->ceiling_rgb_arr[0] = -1;
	map_data->ceiling_rgb_arr[1] = -1;
	map_data->ceiling_rgb_arr[2] = -1;
	map_data->map = NULL;
}

static int	get_file_len(char *path)
{
	int		len;
	int		fd;
	char	*line;

	len = 1;
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		len++;
	}
	free(line);
	close(fd);
	return (len);
}

static int	check_line(t_map *map_data, char *line, int fd)
{
	if (check_for_texture(map_data, line))
		return (0);
	else if (check_for_bonus_texture(map_data, line))
		return (0);
	else if (check_for_rgb(map_data, line))
		return (1);
	else if (check_for_map(map_data, line, fd))
		return (1);
	return (0);
}
