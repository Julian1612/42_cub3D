/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:46:22 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/10 18:47:09 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_get_textures.h"
#include <stdio.h>

// static int	get_data_texture(char *raw_line, char **path);
// static int	get_path_of_texture(char **path, char **line_content);
// static int	get_path_texture(char **texture_path, char *line_content);
int			find_line(char *cub_file_path, char *direction, char **line_content);
static int	get_texture_file_path(t_map *map_data, char *line, int i);

static int	get_texture_file_path(t_map *map_data, char *line, int i)
{
	char **splitted_str;
	char *texture_path;

	splitted_str = ft_split(line, ' ');
	if (splitted_str == NULL)
	{
		error_textures(4);
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

// quasi ne while die einmal durch geht vergelicht strstr ob in der line eine definition da, wenn ja dann
// rein laden in struct.
// die get rgb funktion auch hier direkt mit machen das mach nicht nochmal durber eiern muss
// einfach if c oder f dann rgb values rein schallern
// wenn er auf den anfang der map stößt dann eine funktion die die map in ein array schreibt und einfach bis zum ende rein lad wenn dann
// noche eine definition drin ist muss das spater beim map checken abgefangen werden
int check_for_texture(t_map *map_data, char *line)
{
	// macro definieren der alle sachen enthalt (we, ea, so etc.) und den dann in einer while durch gehen und
	// vergleichen ob verhanden wie unten schon gemacht nor halt das es ein varibaler macro is in dem man nyr ein mal anpassen
	// falls noch eine neue texture hinzu kommt
	char *definitions[4] = {"NO", "SO", "WE", "EA"};
	int	i;

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

int check_for_rgb(t_map *map_data, char *line)
{
	if (ft_strnstr(line, "C", ft_strlen(line)) != NULL
		|| ft_strnstr(line, "F", ft_strlen(line)) != NULL)
	{
		get_rgb_values(map_data, line);
		return (1);
	}
	return (0);
}

int get_map_dimension(char *cub_file_path, int *map_height, int *map_width, char *)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	*map_width = 0;
	fd = open(cub_file_path, O_RDONLY);
	if (fd == -1)
	{
		error_textures(1);
		return (1);
	}
	while(ft_strnstr(line, ))
	while (line != NULL)
	{
		while (/* condition */)
		{
			/* code */
		}

		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strlen(line) > map_width)
			map_width = ft_strlen(line);
		free(line);
		map_height++;
	}
}

int	init_map(t_map *map_data, char *cub_file_path)
{
	int		i;
	int		fd;
	char	*line;
	int		file_len;

	i = 0;
	file_len = get_file_len(cub_file_path);
	while (i < file_len - 1)
	{
		line = get_next_line(fd);
		if (line == NULL && i != file_len - 1)
		{
			error_message(4);
			return (1);
		}

	}
}

int get_map(t_map *map_data, char *line, char *cub_file_path, int fd)
{
	int map_height;
	int map_width;

	if (get_map_dimensions(cub_file_path, &map_height, &map_width))
		return (1);
	// malloc map
	map_data->map = (char **)malloc(sizeof(char *) * (map_height + 1));
	if (map_data->map == NULL)
	{
		error_textures(4);
		return (1);
	}
	map_data->map[map_height] = NULL;
	// init map
	if (init_map(map_data, cub_file_path))
		return (1);
	return (0);
}

int check_for_map(t_map *map_data, char *line, char *cub_file_path, int fd)
{
	int i;

	i = 0;
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	if (line[i] == '1')
	{
		get_map(map_data, line, cub_file_path);
		return (1);
	}
	return (0);
}

int check_line(t_map *map_data, char *line, char *cub_file_path, int fd)
{
	// in der line is eine texture definition return 0
	if(check_for_texture(map_data, line))
		return (0);
	// else if check for bonus textures return 0
	else if (check_for_rgb(map_data, line))
		return (0);
	else if (check_for_map(map_data, line, cub_file_path))
		return (1);
	return (0);
}

int	get_path(t_map *map_data, char *cub_file_path)
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
		if(check_line(map_data, line, cub_file_path, fd))
			break ;
		free(line);
		i++;
	}
	return (0);
}

// static int	get_file_len(char *path)
// {
// 	int		len;
// 	int		fd;
// 	char	*line;

// 	len = 1;
// 	fd = open(path, O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 		len++;
// 	}
// 	free(line);
// 	close(fd);
// 	return (len);
// }

// int	find_line(char *cub_file_path, char *direction, char **line_content)
// {
// 	int		i;
// 	int		fd;
// 	int		file_len;
// 	char	*line;

// 	i = 0;
// 	fd = open(cub_file_path, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		error_message(2);
// 		return (1);
// 	}
// 	file_len = get_file_len(cub_file_path);
// 	while (i < file_len - 1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL && i != file_len - 1)
// 		{
// 			error_message(4);
// 			return (1);
// 		}
// 		if (ft_strnstr(line, direction, ft_strlen(line)) != NULL)
// 		{
// 			cpy_line(line_content, line, ft_strlen(line));
// 			break ;
// 		}
// 		free(line);
// 		i++;
// 	}
// 	// printf("line_content: %s\n", line_content);
// 	// if (check_for_errors(raw_map, direction, count))
// 	// 	return (1);
// 	return (0);
// }


// // static int	get_data_texture(char *raw_line, char **path)
// // {
// // 	char	*line_content;

// // 	line_content = *get_line_content(raw_line);
// // 	if (line_content == NULL)
// // 		return (1);
// // 	if (get_path_texture(path, line_content))
// // 	{
// // 		ft_free_arr(&line_content);
// // 		return (1);
// // 	}
// // 	if (check_file(*path, "xpm"))
// // 	{
// // 		ft_free_arr(&line_content);
// // 		return (1);
// // 	}
// // 	ft_free_arr(&line_content);
// // 	return (0);
// // }

