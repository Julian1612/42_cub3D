/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:14:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/11 16:43:56 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include "../../libraries/libft/src/libft/libft.h" // ft_* functions
#include <unistd.h> // close
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int	check_args(int *argc, char **argv);
int			check_data_type(char *path, char *data_type);
static int	check_for_invalid_definitions(t_map *map_data);

int	parser(int *argc, char **argv, t_game *game)
{
	init_struct_null(&game->map);
	if (check_args(argc, argv))
		return (1);
	if (check_file(argv[1], "cub"))
		return (1);
	if (get_file_data(&game->map, argv[1]))
		return (1);
	if (check_mandatory_textures(&game->map))
		return (1);
	if (check_map(&game->map))
		return (1);
	if (check_for_invalid_definitions(&game->map))
		return (1);
	if (init_player_position(game))
		return (1);
	if (init_sprite_position(game))
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
	while (map_data->arr[i] != NULL)
	{
		j = 0;
		while (map_data->arr[i][j] != '\0')
		{
			if (map_data->arr[i][j] != '0' && map_data->arr[i][j] != '1'
				&& map_data->arr[i][j] != 'N' && map_data->arr[i][j] != 'S'
				&& map_data->arr[i][j] != 'W' && map_data->arr[i][j] != 'E'
				&& map_data->arr[i][j] != 'D' && map_data->arr[i][j] != 'F'
				&& map_data->arr[i][j] != ' ')
				return (error_get_map(5, map_data));
			j++;
		}
		i++;
	}
	return (0);
}
