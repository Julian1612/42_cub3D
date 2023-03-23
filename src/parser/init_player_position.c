/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_position.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:36:05 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/23 15:05:32 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <math.h>
#include <stdio.h>

static double	get_view_direction(char direction);

int	 init_player_position(t_map *map_data, t_player *player_pos)
{
	int	i;
	int	j;

	i = 0;
	while (map_data->map[i])
	{
		j = 0;
		while (map_data->map[i][j])
		{
			if (map_data->map[i][j] == 'N' || map_data->map[i][j] == 'S'
				|| map_data->map[i][j] == 'E' || map_data->map[i][j] == 'W')
			{
				player_pos->x = j;
				player_pos->y = i;
				player_pos->view_dir = get_view_direction(map_data->map[i][j]);
				return (0);
			}
			j++;
		}
		i++;
	}
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
