/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:46:22 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/07 17:46:47 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_get_textures.h"
#include <stdio.h>

static int	get_data_texture(char *raw_line, char **path);
static int	get_path_of_texture(char **path, char **line_content);
static int	get_path_texture(char **texture_path, char *line_content);

int	get_path(char *direction, char **texture_path, char *cub_file_path)
{
	int	i;
	char *line_content;

	i = 0;
	line_content = NULL;
	if (find_line(cub_file_path, direction, &line_content))
		return (1);
	if (get_path_of_texture(texture_path, &line_content))
		return (1);
	return (0);
}

static int	get_path_texture(char **texture_path, char *line_content)
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
	if (cpy_line(texture_path, splitted_str[1], ft_strlen(line_content[1]) - 1) == NULL)
		return (1);
	printf("texture_path: %s\n", *texture_path);
	return (0);
}

static int	get_data_texture(char *raw_line, char **path)
{
	char	*line_content;

	line_content = get_line_content(raw_line);
	if (line_content == NULL)
		return (1);
	if (get_path_texture(path, line_content))
	{
		ft_free_arr(line_content);
		return (1);
	}
	if (check_file(*path, "xpm"))
	{
		ft_free_arr(line_content);
		return (1);
	}
	ft_free_arr(line_content);
	return (0);
}

