/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_position.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:36:05 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/07 17:48:23 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <math.h>
#include <stdio.h>

static double	get_view_direction(char direction);
static void		search_for_player(t_player *player_pos, int i,
					char *line, int *def_count);

int	init_player_position(t_map *map_data, t_player *player_pos)
{
	int	i;
	int	def_count;

	i = 0;
	def_count = 0;
	while (map_data->map[i])
	{
		search_for_player(player_pos, i, map_data->map[i], &def_count);
		i++;
	}
	if (def_count == 1)
		return (0);
	else if (def_count > 1)
		return (error_get_map(6, map_data));
	return (error_get_map(4, map_data));
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

void	search_for_player(t_player *player_pos, int i,
			char *line, int *def_count)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] == 'N' || line[j] == 'S'
			|| line[j] == 'E' || line[j] == 'W')
		{
			player_pos->x = j;
			player_pos->y = i;
			player_pos->view_dir = get_view_direction(line[j]);
			(*def_count)++;
		}
		j++;
	}
}
