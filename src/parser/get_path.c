/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:46:22 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/12 11:31:35 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdlib.h>

// static int	get_data_texture(char *raw_line, char **path);
// static int	get_path_of_texture(char **path, char **line_content);
// static int	get_path_texture(char **texture_path, char *line_content);
static int	get_texture_file_path(t_map *map_data, char *line, int i);

int	get_file_data(t_map *map_data, char *cub_file_path)
{
	int		i;
	char	*line;
	int		file_len;
	int		fd;

	i = 0;
	line = NULL;
	file_len = get_file_len(cub_file_path);
	fd = open(cub_file_path, O_RDONLY);
	if (fd == -1)
	{
		error_message(2);
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
		if (check_line(map_data, line, fd))
			break ;
		free(line);
		i++;
	}
	return (0);
}

static int	get_texture_file_path(t_map *map_data, char *line, int i)
{
	char	**splitted_str;
	char	*texture_path;

	splitted_str = ft_split(line, ' ');
	if (splitted_str == NULL)
	{
		// error_textures(4);
		return (1);
	}
	if (i == 0)
		cpy_line(&map_data->north, splitted_str[1], ft_strlen(splitted_str[1]));
	else if (i == 1)
		cpy_line(&map_data->south, splitted_str[1], ft_strlen(splitted_str[1]));
	else if (i == 2)
		cpy_line(&map_data->west, splitted_str[1], ft_strlen(splitted_str[1]));
	else if (i == 3)
		cpy_line(&map_data->east, splitted_str[1], ft_strlen(splitted_str[1]));
	ft_free_arr(splitted_str);
	return (0);
}

static int	check_for_texture(t_map *map_data, char *line)
{
	static char	*definitions[4] = {"NO", "SO", "WE", "EA"};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (ft_strnstr(line, definitions[i], ft_strlen(line)) != NULL)
		{
			get_texture_file_path(map_data, line, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_rgb_values(char **line_content)
{
	if (ft_atoi(line_content[0]) > 255 || ft_atoi(line_content[1]) > 255
		|| ft_atoi(line_content[2]) > 255)
	{
		error_textures(17);
		return (1);
	}
	if (ft_atoi(line_content[0]) < 0 || ft_atoi(line_content[1]) < 0
		|| ft_atoi(line_content[2]) < 0)
	{
		error_textures(17);
		return (1);
	}
	return (0);
}

static int	get_rgb_values(t_map *map_data, char *line)
{
	char	**splitted_str;
	int		boundary;

	boundary = 0;
	splitted_str = ft_split(line, ',');
	if (splitted_str == NULL)
	{
		error_textures(4);
		return (1);
	}
	if (ft_arrlen(splitted_str) != 3)
	{
		error_textures(14);
		return (1);
	}
	boundary = remove_letter(splitted_str);
	if (check_rgb_values(&line))
		return (1);
	if (boundary == 1)
	{
		map_data->ceiling_rgb_arr[0] = ft_atoi(splitted_str[0]);
		map_data->ceiling_rgb_arr[1] = ft_atoi(splitted_str[1]);
		map_data->ceiling_rgb_arr[2] = ft_atoi(splitted_str[2]);
	}
	else if (boundary == 2)
	{
		map_data->floor_rgb_arr[0] = ft_atoi(splitted_str[0]);
		map_data->floor_rgb_arr[1] = ft_atoi(splitted_str[1]);
		map_data->floor_rgb_arr[2] = ft_atoi(splitted_str[2]);
	}
	ft_free_arr(splitted_str);
	return (0);
}


int	check_for_rgb(t_map *map_data, char *line)
{
	if (ft_strnstr(line, "C", ft_strlen(line)) != NULL
		|| ft_strnstr(line, "F", ft_strlen(line)) != NULL)
	{
		get_rgb_values(map_data, line);
		return (1);
	}
	return (0);
}

// eigns file checkline.c
int	check_line(t_map *map_data, char *line, int fd)
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
