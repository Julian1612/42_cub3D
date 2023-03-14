/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:47:45 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/14 18:02:16 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"

static int	get_texture_file_path(t_map *map_data, char *line, int i);
static int	get_bonus_texture_file_path(t_map *map_data, char *line, int i);

int	check_for_texture(t_map *map_data, char *line)
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

static int	get_texture_file_path(t_map *map_data, char *line, int i)
{
	char	**splitted_str;
	char	*texture_path;
	int		splitted_str_len;

	splitted_str = ft_split(line, ' ');
	splitted_str_len = ft_strlen(splitted_str[1]);
	if (splitted_str == NULL)
	{
		error_message(4);
		return (1);
	}
	if (i == 0)
		cpy_line(&map_data->north, splitted_str[1], splitted_str_len);
	else if (i == 1)
		cpy_line(&map_data->south, splitted_str[1], splitted_str_len);
	else if (i == 2)
		cpy_line(&map_data->west, splitted_str[1], splitted_str_len);
	else if (i == 3)
		cpy_line(&map_data->east, splitted_str[1], splitted_str_len);
	ft_free_arr(splitted_str);
	return (0);
}

char	*cpy_line(char **des, char *src, int len)
{
	int	i;

	i = 0;
	*des = malloc(sizeof(char) * (len + 1));
	if (*des == NULL)
	{
		error_message(4);
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
	static char	*definitions[NBR_B_TEXTURES] = {DOOR, BARREL, ENEMY};
	int			i;

	i = 0;
	while (i < NBR_B_TEXTURES)
	{
		if (ft_strnstr(line, definitions[i], ft_strlen(line)) != NULL)
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
	{
		error_message(4);
		return (1);
	}
	if (i == 0)
		cpy_line(&map_data->door, splitted_str[1], splitted_str_len);
	else if (i == 1)
		cpy_line(&map_data->barrel, splitted_str[1], splitted_str_len);
	else if (i == 2)
		cpy_line(&map_data->enemy, splitted_str[1], splitted_str_len);
	ft_free_arr(splitted_str);
	return (0);
}
