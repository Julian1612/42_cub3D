/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:59:24 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/12 19:40:37 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libraries/libft/src/libft/libft.h" // ft_* functions
#include "../../libraries/libft/src/get_next_line/get_next_line.h"
#include "private_parser.h"
#include "string.h" // NULL

void	init_struct_null(t_map *map_data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		map_data->textures[i].path = NULL;
		i++;
	}
	map_data->ceiling_color = -1;
	map_data->floor_color = -1;
	map_data->ceiling_color = -1;
	map_data->floor_color = -1;
	map_data->arr = NULL;
	map_data->enemies = NULL;
	map_data->doors = NULL;
	map_data->door_count = 0;
	map_data->enemy_count = 0;
}

int	is_all_digit(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if ((str[i][j] < '0' || str[i][j] > '9')
			&& str[i][j] != ' ' && str[i][j] != '\n')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

bool	contains_only_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

int	check_for_new_line(char **splitted_str, int *error)
{
	if (splitted_str[0][0] == '\n' || splitted_str[1][0] == '\n'
	|| splitted_str[2][0] == '\n')
	{
		ft_free_arr((void **)splitted_str);
		*error = 1;
		return (1);
	}
	return (0);
}

void	clear_buffer(char **line)
{
	get_next_line(-1);
	if (*line != NULL)
	{
		free(*line);
		*line = NULL;
	}
}
