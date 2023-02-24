/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_position.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:36:05 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/23 20:56:54 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_player_position.h"

int	init_player_position(t_map *map_data, t_player *player)
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
				player->x = j + 0.5;
				player->y = i + 0.5;
				player->direction = map_data->map[i][j];
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
