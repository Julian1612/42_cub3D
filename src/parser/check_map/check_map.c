/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:13:29 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/17 13:49:50 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
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
				error_message(16);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
