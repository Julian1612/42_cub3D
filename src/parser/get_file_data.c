/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:46:22 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/24 10:37:12 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdlib.h>
#include <stdio.h>

static int	read_map_data(t_map *map_data, int fd, int file_len);
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
	if (read_map_data(map_data, fd, file_len))
		return (ERROR);
	close(fd);
	return (SUCCSES);
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
			return (ERROR);
		if (check_line(map_data, line, fd))
			break ;
		free(line);
		line = NULL;
		i++;
	}
	get_next_line(-1);
	if (line != NULL)
	{
		free(line);
		line = NULL;
	}
	return (SUCCSES);
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
		return (SUCCSES);
	else if (check_for_bonus_texture(map_data, line))
		return (SUCCSES);
	else if (check_for_rgb(map_data, line))
		return (ERROR);
	else if (check_for_map(map_data, line, fd))
		return (ERROR);
	return (SUCCSES);
}
