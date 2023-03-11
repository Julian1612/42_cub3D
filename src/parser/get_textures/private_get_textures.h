/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_get_textures.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:24:04 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/11 16:16:06 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_GET_TEXTURES_H
# define PRIVATE_GET_TEXTURES_H
# include "../private_parser.h"

void	error_textures(int error_code);

void	free_textures(t_map *map_data);

char	*cpy_line(char **des, char *src, int len);

char	**get_line_content(char *raw_line);

// int     find_line(char *cub_file_path, char *direction, char **line_content);

int	remove_letter(char **line_content);

int	get_path(t_map *map_data, char *cub_file_path);

int     get_map_color(char *rgb_values, int *rgb_arr, char *cub_file_path);

// int	get_textures(t_map *map_data, char *path);

#endif
