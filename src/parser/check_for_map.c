/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:47:06 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/10 18:26:03 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include "libraries/libft/src/get_next_line/get_next_line.h" // get_next_line
#include "libraries/libft/src/libft/libft.h" // ft_strlen, ft_strdup, ft_strjoin_cub3d, ft_split

static int	init_map(t_map *map_data, char *line, int fd, int *error);
static int	init_map_str(t_map *map_data, char *line, char **map_str);

int	check_for_map(t_map *map_data, char *line, int fd, int *error)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	if (line[i] == '1')
	{
		init_map(map_data, line, fd, error);
		return (1);
	}
	return (0);
}

static int	init_map(t_map *map_data, char *line, int fd, int *error)
{
	char	*map_str;

	if (init_map_str(map_data, line, &map_str))
		return (1);
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strlen(line) > 0 && line[0] == '\n')
		{
			*error = 1;
			error_get_map(1, map_data);
			break ;
		}
		if (line != NULL)
			map_str = ft_strjoin_free_s1(map_str, line);
		free(line);
	}
	get_next_line(-1);
	if (*error == 0)
		map_data->arr = ft_split(map_str, '\n');
	free(map_str);
	free(line);
	return (0);
}

static int	init_map_str(t_map *map_data, char *line, char **map_str)
{
	*map_str = ft_strdup(line);
	if (*map_str == NULL)
		return (error_message(4, map_data));
	return (0);
}
