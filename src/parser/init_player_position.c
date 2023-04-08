/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_position.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:36:05 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/08 22:24:35 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <math.h>
#include <stdio.h>

static double	get_view_direction(char direction);
static int		search_for_player(t_game *game, int i,
					char *line, int *def_count);

int	init_player_position(t_game *game)
{
	int	i;
	int	def_count;

	i = 0;
	def_count = 0;
	while (game->map.map[i])
	{
		if (search_for_player(game, i, game->map.map[i], &def_count))
			return (1);
		i++;
	}
	if (def_count == 1)
		return (0);
	else if (def_count > 1)
		return (error_get_map(6, &game->map));
	return (error_get_map(4, &game->map));
}

static double	get_view_direction(char direction)
{
	if (direction == 'N')
		return (M_PI);
	else if (direction == 'S')
		return (0);
	else if (direction == 'E')
		return (M_PI * 3 / 2);
	else if (direction == 'W')
		return (M_PI / 2);
	return (0);
}

static int	search_for_player(t_game *game, int i,
			char *line, int *def_count)
{
	int	j;
	int	line_len;

	j = 0;
	while (line[j])
	{
		line_len = ft_strlen(line);
		if (line[j] == 'N' || line[j] == 'S'
			|| line[j] == 'E' || line[j] == 'W')
		{
			if ((j == 0 || j == line_len -1)
				|| (j < line_len && line[j + 1] == ' ')
				|| (j > 0 && line[j - 1] == ' '))
				return (error_get_map(8, &game->map));
			game->player.x = j + 0.5;
			game->player.y = i + 0.5;
			game->player.view_dir = get_view_direction(line[j]);
			(*def_count)++;
		}
		j++;
	}
	return (0);
}
