/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:13:29 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/16 17:05:39 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdio.h>

static int	check_wall(char **map);

int	check_map(char **map)
{
	if (check_wall(map))
		return (1);
	// if (check_for_invalid_chars(map))
	// 	return (1);
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

