/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_get_map.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:23:21 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/11 16:17:32 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_GET_MAP_H
# define PRIVATE_GET_MAP_H
# include "../private_parser.h"
# define NBR_POSSIBLE_DEFINITIONS 6

// int	check_map(char **map);

// int	check_wall_horizontal(char **raw_map);

// int	check_wall_vertical(char **raw_map);

// void	error_get_map(int error_code);

// // int	get_map(t_map *map_data, char **raw_map);

// int	malloc_map(char ***map, int map_height, int map_width);

// int	init_map_arr(char **line, t_map *map_data, int fd, char *cub_file_path);

int	init_map(t_map *map_data, char *line, int fd);
int check_for_map(t_map *map_data, char *line, int fd);

#endif
