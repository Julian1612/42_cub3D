/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_parser.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:13:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/10 13:54:04 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_PARSER_H
# define PRIVATE_PARSER_H
# include "../cub3D.h"
# include "get_map.h"
# include "get_textures.h"
# define ARRAY_SIZE 7
# define TEXTURES_ARR {"NO", "SO", "WE", "EA", "F", "C", "D"}

// parser.c
int		parser(int *argc, char **argv, t_map *map_data);

// check_args.c
int		check_args(int *argc, char **argv);

// check_file.c
int	check_file(char *cub_file_path, char *data_type);

// put_file_content_in_arr.c
int		put_file_content_in_arr(char ***raw_map, char *path);

// get_textures.c
int	get_textures(t_map *map_data, char *path);

// get_map.c
int	get_map(t_map *map_data, char *cub_file_path);

// error_message.c
void	error_message(int error_code);

#endif
