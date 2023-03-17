/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_position.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:36:05 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/17 10:18:40 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"

int	init_player_position(t_map *map_data)
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
				map_data->starting_pos_x = j;
				map_data->starting_pos_y = i;
				map_data->starting_dir = map_data->map[i][j];
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
