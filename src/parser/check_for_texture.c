/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:47:45 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/07 15:21:42 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>

static int	get_texture_file_path(t_map *map_data, char *line, int i, int *error);
static int	get_bonus_texture_file_path(t_map *map_data, char *line, int i);

int	check_for_texture(t_map *map_data, char *line, int *error)
{
	static char	*definitions[4] = {"NO", "SO", "WE", "EA"};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (ft_strnstr(line, definitions[i], ft_strlen(line)) != NULL)
		{
			get_texture_file_path(map_data, line, i, error);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	get_texture_file_path(t_map *map_data, char *line, int i, int *error)
{
	char	**splitted_str;
	char	*texture_path;
	int		splitted_str_len;

	splitted_str = ft_split(line, ' ');
	if (splitted_str == NULL || ft_arrlen((void **)splitted_str) != 2)
	{
		*error = 1;
		return (error_message(8, map_data));
	}
	splitted_str_len = ft_strlen(splitted_str[1]);
	if (splitted_str == NULL)
		return (error_message(4, map_data));
	if (i == 0)
	{
		if (map_data->objects[NORTH].path != NULL)
		{
			*error = 1;
			return (error_message(5, map_data));
		}
		cpy_line(&map_data->objects[NORTH].path, splitted_str[1], splitted_str_len);
	}
	else if (i == 1)
	{
		if (map_data->objects[SOUTH].path != NULL)
		{
			*error = 1;
			return (error_message(5, map_data));
		}
		cpy_line(&map_data->objects[SOUTH].path, splitted_str[1], splitted_str_len);
	}
	else if (i == 2)
	{
		if (map_data->objects[WEST].path != NULL)
		{
			*error = 1;
			return (error_message(5, map_data));
		}
		cpy_line(&map_data->objects[WEST].path, splitted_str[1], splitted_str_len);
	}
	else if (i == 3)
	{
		if (map_data->objects[EAST].path != NULL)
		{
			*error = 1;
			return (error_message(5, map_data));
		}
		cpy_line(&map_data->objects[EAST].path, splitted_str[1], splitted_str_len);
	}
	ft_free_arr((void **)splitted_str);
	return (0);
}

char	*cpy_line(char **des, char *src, int len)
{
	int	i;

	i = 0;
	*des = malloc(sizeof(char) * (len + 1));
	if (*des == NULL)
	{
		error_message(4, NULL);
		return (NULL);
	}
	while (i < len - 1)
	{
		(*des)[i] = src[i];
		i++;
	}
	(*des)[i] = '\0';
	return (*des);
}

int	check_for_bonus_texture(t_map *map_data, char *line)
{
	static char	definitions[NBR_B_TEXTURES] = {CHAR_DOOR, CHAR_BARREL, CHAR_ENEMY};
	int			i;

	i = 0;
	while (i < NBR_B_TEXTURES)
	{
		if (ft_strchr(line, definitions[i]) != NULL)
		{
			get_bonus_texture_file_path(map_data, line, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	get_bonus_texture_file_path(t_map *map_data, char *line, int i)
{
	char	**splitted_str;
	char	*texture_path;
	int		splitted_str_len;

	splitted_str = ft_split(line, ' ');
	splitted_str_len = ft_strlen(splitted_str[1]);
	if (splitted_str == NULL)
		return (error_message(4, map_data));
	if (i == 0)
		cpy_line(&map_data->objects[DOOR].path, splitted_str[1], splitted_str_len);
	else if (i == 1)
		cpy_line(&map_data->objects[BARREL].path, splitted_str[1], splitted_str_len);
	// else if (i == 2)
	// 	cpy_line(&map_data->enemy.path, splitted_str[1], splitted_str_len);
	ft_free_arr((void **)splitted_str);
	return (0);
}
