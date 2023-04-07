/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:14:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/07 18:56:31 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int	check_args(int *argc, char **argv);
int			check_data_type(char *path, char *data_type);
static int	check_for_invalid_definitions(t_map *map_data);

int	parser(int *argc, char **argv, t_map *map_data, t_player *player_pos)
{
	init_struct_null(map_data);
	if (check_args(argc, argv))
		return (1);
	if (check_file(argv[1], "cub"))
		return (1);
	if (get_file_data(map_data, argv[1]))
		return (1);
	if (check_mandatory_textures(map_data))
		return (1);
	if (check_map(map_data))
		return (1);
	if (check_bonus_textures(map_data))
		return (1);
	if (check_for_invalid_definitions(map_data))
		return (1);
	if (init_player_position(map_data, player_pos))
		return (1);
	return (0);
}

static int	check_args(int *argc, char **argv)
{
	if (*argc != 2)
		return (error_message(1, NULL));
	if (argv[1][0] == '\0')
		return (1);
	return (0);
}

int	check_file(char *cub_file_path, char *data_type)
{
	int	fd;

	fd = open(cub_file_path, O_RDONLY);
	if (fd < 0)
		return (error_message(2, NULL));
	close(fd);
	if (check_data_type(cub_file_path, data_type))
		return (error_message(3, NULL));
	return (0);
}

int	check_data_type(char *path, char *data_type)
{
	int	path_len;
	int	len_type;

	path_len = ft_strlen(path);
	len_type = ft_strlen(data_type);
	if (path_len >= len_type
		&& ft_strncmp(path + (path_len - len_type), data_type, len_type))
		return (1);
	return (0);
}

static int	check_for_invalid_definitions(t_map *map_data)
{
	int			i;
	int			j;

	i = 0;
	while (map_data->map[i] != NULL)
	{
		j = 0;
		while (map_data->map[i][j] != '\0')
		{
			if (map_data->map[i][j] != '0' && map_data->map[i][j] != '1'
				&& map_data->map[i][j] != 'N' && map_data->map[i][j] != 'S'
				&& map_data->map[i][j] != 'W' && map_data->map[i][j] != 'E'
				&& map_data->map[i][j] != 'D' && map_data->map[i][j] != 'B'
				&& map_data->map[i][j] != 'E' && map_data->map[i][j] != ' ')
				return (error_get_map(5, map_data));
			j++;
		}
		i++;
	}
	return (0);
}
