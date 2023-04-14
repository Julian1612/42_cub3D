/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_player_position.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:36:05 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/14 02:01:01 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include "../../libraries/libft/src/libft/libft.h" // ft_* functions
#include "../cub3D.h" // t_vec
#include <math.h>
#include <stdio.h>

static t_vec	get_view_direction(char direction);
static int		search_for_player(t_game *game, int i,
					char *line, int *def_count);

int	init_player_position(t_game *game)
{
	int	i;
	int	def_count;

	i = 0;
	def_count = 0;
	game->map.height = ft_arrlen((void **)game->map.arr);
	while (game->map.arr[i])
	{
		if (search_for_player(game, i, game->map.arr[i], &def_count))
			return (1);
		i++;
	}
	if (def_count == 1)
		return (0);
	else if (def_count > 1)
		return (error_get_map(6, &game->map));
	return (error_get_map(4, &game->map));
}

static t_vec	get_view_direction(char direction)
{
	t_vec	dir;

	if (direction == 'N')
	{
		dir.x = 0;
		dir.y = -1;
	}
	else if (direction == 'S')
	{
		dir.x = 0;
		dir.y = 1;
	}
	else if (direction == 'E')
	{
		dir.x = 1;
		dir.y = 0;
	}
	else
	{
		dir.x = -1;
		dir.y = 0;
	}
	return (dir);
}

static t_vec	get_camera_direction(char direction)
{
	t_vec	cplane;

	if (direction == 'N')
	{
		cplane.x = (double)WIDTH / HEIGHT / 2;
		cplane.y = 0;
	}
	else if (direction == 'S')
	{
		cplane.x = -(double)WIDTH / HEIGHT / 2;
		cplane.y = 0;
	}
	else if (direction == 'E')
	{
		cplane.x = 0;
		cplane.y = (double)WIDTH / HEIGHT / 2;
	}
	else
	{
		cplane.x = 0;
		cplane.y = -(double)WIDTH / HEIGHT / 2;
	}
	return (cplane);
}

static int	search_for_player(t_game *game, int i,
			char *line, int *def_count)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] == 'N' || line[j] == 'S'
			|| line[j] == 'E' || line[j] == 'W')
		{
			if (check_pos_in_map(&game->map, i, j))
				return (1);
			game->player.pos.x = j + 0.5;
			game->player.pos.y = i + 0.5;
			game->player.dir = get_view_direction(line[j]);
			game->player.cplane = get_camera_direction(line[j]);
			(*def_count)++;
		}
		j++;
	}
	return (0);
}
