/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_get_map.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:23:21 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/22 14:22:47 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_GET_MAP_H
# define PRIVATE_GET_MAP_H
# include "../private_parser.h"

int	check_map(char **map);

int	check_wall_horizontal(char **raw_map);

int	check_wall_vertical(char **raw_map);

void	error_get_map(int error_code);

// int	get_map(t_map *map_data, char **raw_map);

int	malloc_map(char ***map, int map_height, int map_width);

int	map_to_arr(char **raw_map, t_map *map_data, int start_map);

#endif
