/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:13:29 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/09 17:32:43 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_get_map.h"
#include <stdio.h>

static int	check_wall(char **map);
static int	check_for_invalid_chars(char **map);

int	check_map(char **map)
{
	if (check_wall(map))
		return (1);
	if (check_for_invalid_chars(map))
		return (1);
	return (0);
}

static int	check_wall(char **map)
{
	if (check_wall_horizontal(map))
		return (1);
	if (check_wall_vertical(map))
		return (1);
	return (0);
}


static int	check_for_invalid_chars(char **map)
{
	// auf alle texturen prüfen auch bonus !!
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != '2'
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != 'W' && map[i][j] != ' ')
			{
				ft_free_arr(map);
				error_get_map(16);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
