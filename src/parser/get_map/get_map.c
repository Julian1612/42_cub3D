/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:08:23 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/10 17:18:17 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_get_map.h"
#include <stdio.h>

static int	find_map_in_file(int fd, char **line, int file_len);
static int	check_for_texture(char **raw_map, int *i, int j, int *flage);
static int	validate_map_position(char **raw_map, int i, int j, int flage);
static int	remove_newline_from_arr(char **raw_map, int i);
static int	defs_counter(int *count_def, char *cub_file_path, int file_len);

// die function muss irgendwo nei ballerd werden wo alle path und get map zu greifen koenne
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

// @todo add the other textures from the bonus
static int	defs_counter(int *count_def, char *cub_file_path, int file_len)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(cub_file_path, O_RDONLY);
	if (fd == -1)
	{
		return (1);
	}
	while (i < file_len - 1)
	{
		line = get_next_line(fd);
		if (line == NULL && i != file_len - 1)
		{
			error_message(4);
			return (1);
		}
		if (ft_strnstr(line, "WE", ft_strlen(line)) != NULL)
			(*count_def)++;
		else if (ft_strnstr(line, "EA", ft_strlen(line)) != NULL)
			(*count_def)++;
		else if (ft_strnstr(line, "SO", ft_strlen(line)) != NULL)
			(*count_def)++;
		else if (ft_strnstr(line, "NO", ft_strlen(line)) != NULL)
			(*count_def)++;
		else if (ft_strnstr(line, "C", ft_strlen(line)) != NULL)
			(*count_def)++;
		else if (ft_strnstr(line, "F", ft_strlen(line)) != NULL)
			(*count_def)++;
		free(line);
		i++;
	}
	if (*count_def != 6)
	{
		close(fd);
		error_message(4);
		return (1);
	}
	close(fd);
	return (0);
}


// erst die  map dimensionen bestimmen width and height
// dann die map in der file finden
// dann die map in ein array speichern
int	get_map(t_map *map_data, char *cub_file_path)
{
	int		fd;
	int		file_len;
	char	*line;
	int		count_def;

	line = NULL;
	count_def = 0;
	fd = open(cub_file_path, O_RDONLY);
	// fd check !!!
	file_len = get_file_len(cub_file_path);
	if (defs_counter(&count_def, cub_file_path, file_len))
		return (1);
	if (find_map_in_file(fd, &line, file_len))
		return (1);
	// if (remove_newline_from_arr(raw_map, start_map))
	// 	return (1);
	if (init_map_arr(line, map_data, fd, cub_file_path))
		return (1);
	// if (check_map(map_data->map))
	// 	return (1);
	return (0);
}

static int	find_map_in_file(int fd, char **line, int file_len)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < file_len - 1)
	{
		*line = get_next_line(fd);
		if (*line == NULL && i != file_len - 1)
		{
			error_message(4);
			return (1);
		}
		while (*line[j] != '\0' && *line[j] == ' ')
			j++;
		if (*line[j] == '1')
			return (0);
		free(*line);
		i++;
	}
	error_get_map(9);
	return (1);
}

// static int	check_for_texture(char **raw_map, int *i, int j, int *flage)
// {
// 	if (raw_map[*i][j] == 'S' || raw_map[*i][j] == 'N'
// 		|| raw_map[*i][j] == 'W' || raw_map[*i][j] == 'E'
// 		|| raw_map[*i][j] == 'C' || raw_map[*i][j] == 'F')
// 	{
// 		(*flage)++;
// 		return (1);
// 	}
// 	return (0);
// }

// static int	validate_map_position(char **raw_map, int i, int j, int flage)
// {
// 	if (flage < 6 && raw_map[i][j] == '1')
// 	{
// 		ft_free_arr(raw_map);
// 		error_get_map(13);
// 		return (1);
// 	}
// 	return (0);
// }
// @todo kann ich den shit einfach null terminiueren oder muss da was anderes gemadhrt weren

int static	remove_newline_from_arr(char **raw_map, int i)
{
	int		j;

	while (raw_map[i] != NULL)
	{
		j = 0;
		if (raw_map[i][0] == '\n')
		{
			error_get_map(15);
			ft_free_arr(raw_map);
			return (1);
		}
		while (raw_map[i][j] != '\0')
		{
			if (raw_map[i][j] == '\n')
				raw_map[i][j] = '\0';
			j++;
		}
		i++;
	}
	return (0);
}
