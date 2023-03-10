/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:46:22 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/09 21:18:28 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_get_textures.h"
#include <stdio.h>

// static int	get_data_texture(char *raw_line, char **path);
// static int	get_path_of_texture(char **path, char **line_content);
// static int	get_path_texture(char **texture_path, char *line_content);
int			find_line(char *cub_file_path, char *direction, char **line_content);
static int	get_texture_file_path(char **texture_path, char *line_content);

static int	get_texture_file_path(char **texture_path, char *line_content)
{
	char **splitted_str;

	splitted_str = ft_split(line_content, ' ');
	*texture_path = malloc(sizeof(char) * ft_strlen(splitted_str[1]));
	if (*texture_path == NULL)
	{
		error_textures(4);
		return (1);
	}
	// checken of split 2 elemente hat
	// error returnen
	if (cpy_line(texture_path, splitted_str[1], ft_strlen(&line_content[1]) - 1) == NULL)
		return (1);
	return (0);
}
`
// quasi ne while die einmal durch geht vergelicht strstr ob in der line eine definition da, wenn ja dann
// rein laden in struct.
// die get rgb funktion auch hier direkt mit machen das mach nicht nochmal durber eiern muss
// einfach if c oder f dann rgb values rein schallern
// wenn er auf den anfang der map stößt dann eine funktion die die map in ein array schreibt und einfach bis zum ende rein lad wenn dann
// noche eine definition drin ist muss das spater beim map checken abgefangen werden
int check_for_texture(char *line, char **texture_path)
{

	// macro definieren der alle sachen enthalt (we, ea, so etc.) und den dann in einer while durch gehen und
	// vergleichen ob verhanden wie unten schon gemacht nor halt das es ein varibaler macro is in dem man nyr ein mal anpassen
	// falls noch eine neue texture hinzu kommt
	char *definitions[];

	definitions = ["WE", "EA", "SO", "NO"]
	// die bonus texturen noch da zu !!!
	if (ft_strstr(line, "WE", ft_strlen(line)) != NULL)
	{
		get_texture_file_path(texture_path, line);
		return (0)
	}
	else if (ft_strstr(line, "EA", ft_strlen(line)) != NULL)
	{
		get_texture_file_path(texture_path, line);
		return (0)
	}
	else if (ft_strstr(line, "SO", ft_strlen(line)) != NULL)
	{
		get_texture_file_path(texture_path, line);
		return (0)
	}
	else if (ft_strstr(line, "NO", ft_strlen(line)) != NULL)
	{
		get_texture_file_path(texture_path, line);
		return (0)
	}
	return (0);
}

int check_line(char **texture_path, char *line)
{
	// in der line is eine texture definition return 0
	if(check_for_texture(line, texture_path))
		return (0);
	else if (check_fo)
	// else if in der line is eine rgb definition return 0
	// else if in der line beginnt die map return 1
	return (0);
}

int	get_path(char *direction, char **texture_path, char *cub_file_path)
{
	int		i;
	char	*line;
	int		file_len;
	int		fd;

	i = 0;
	line = NULL;
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
		if(check_line(line, texture_path))
			break ;
		free(line);
		i++;
	}
	if (get_texture_file_path(texture_path, line))
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

int	find_line(char *cub_file_path, char *direction, char **line_content)
{
	int		i;
	int		fd;
	int		file_len;
	char	*line;

	i = 0;
	fd = open(cub_file_path, O_RDONLY);
	if (fd == -1)
	{
		error_message(2);
		return (1);
	}
	file_len = get_file_len(cub_file_path);
	while (i < file_len - 1)
	{
		line = get_next_line(fd);
		if (line == NULL && i != file_len - 1)
		{
			error_message(4);
			return (1);
		}
		if (ft_strnstr(line, direction, ft_strlen(line)) != NULL)
		{
			cpy_line(line_content, line, ft_strlen(line));
			break ;
		}
		free(line);
		i++;
	}
	// printf("line_content: %s\n", line_content);
	// if (check_for_errors(raw_map, direction, count))
	// 	return (1);
	return (0);
}


// static int	get_data_texture(char *raw_line, char **path)
// {
// 	char	*line_content;

// 	line_content = *get_line_content(raw_line);
// 	if (line_content == NULL)
// 		return (1);
// 	if (get_path_texture(path, line_content))
// 	{
// 		ft_free_arr(&line_content);
// 		return (1);
// 	}
// 	if (check_file(*path, "xpm"))
// 	{
// 		ft_free_arr(&line_content);
// 		return (1);
// 	}
// 	ft_free_arr(&line_content);
// 	return (0);
// }

