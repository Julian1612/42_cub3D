/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:46:22 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/11 14:37:38 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include "../../libraries/libft/src/get_next_line/get_next_line.h"
#include <fcntl.h> // open
#include <unistd.h> // close
#include <stdlib.h>
#include <stdio.h>

static int	read_map_data(t_map *map_data, int fd, int file_len);
static int	get_file_len(char *path);
static int	check_line(t_map *map_data, char *line, int fd, int *error);

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
		return (1);
	close(fd);
	return (0);
}

static int	read_map_data(t_map *map_data, int fd, int file_len)
{
	int		i;
	char	*line;
	int		error;

	i = 0;
	error = 0;
	while (i < file_len - 1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (error_message(4, map_data));
		if (check_line(map_data, line, fd, &error))
		{
			if (error == 1)
				return (clear_mem(&line));
			break ;
		}
		if (error == 1)
			return (clear_mem(&line));
		free(line);
		line = NULL;
		i++;
	}
	clear_buffer(&line);
	return (0);
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

int	check_for_invalid_definition(t_map *map_data, char *line, int *error)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != ' ')
	{
		if (line[i] != 'S' && line[i] != 'W'
			&& line[i] != 'E' && line[i] != 'N'
			&& line[i] != 'F' && line[i] != 'C'
			&& line[i] != ' ' && line[i] != '\n')
		{
			*error = 1;
			return (error_textures_2(1, map_data));
		}
		i++;
	}
	return (0);
}

static int	check_line(t_map *map_data, char *line, int fd, int *error)
{
	if (check_for_texture(map_data, line, error))
		return (0);
	else if (check_for_rgb(map_data, line, error))
		return (0);
	else if (check_for_map(map_data, line, fd, error))
		return (1);
	else if (check_for_invalid_definition(map_data, line, error))
		return (0);
	return (0);
}
