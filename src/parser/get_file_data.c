/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:46:22 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/12 17:02:39 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdlib.h>

static int	get_file_len(char *path);
static int	get_fd(char *path);
static int	check_line(t_map *map_data, char *line, int fd);

int	get_file_data(t_map *map_data, char *cub_file_path)
{
	int		i;
	char	*line;
	int		file_len;
	int		fd;

	i = 0;
	file_len = get_file_len(cub_file_path);
	fd = get_fd(cub_file_path);
	while (i < file_len - 1)
	{
		line = get_next_line(fd);
		if (line == NULL && i != file_len - 1)
		{
			error_message(4);
			return (1);
		}
		if (check_line(map_data, line, fd))
			break ;
		free(line);
		i++;
	}
	return (0);
}

static int	get_fd(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		error_message(2);
		return (1);
	}
	return (fd);
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
	// else if check for bonus textures return 0
	else if (check_for_rgb(map_data, line))
		return (0);
	else if (check_for_map(map_data, line, fd))
		return (1);
	return (0);
}
