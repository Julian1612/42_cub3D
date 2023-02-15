/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:13:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/15 14:54:59 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "./../../includes/cub3D.h"

typedef struct s_map
{
	char			*we;
	char			*ea;
	char			*so;
	char			*no;
	int				ceiling_r;
	int				ceiling_g;
	int				ceiling_b;
	int				floor_r;
	int				floor_g;
	int				floor_b;
	char			**map;
}				t_map;

// parser.c
int		parser(int *argc, char **argv, t_map *map_data);

// error_message.c
void	error_message(int error_code);

// map_to_arr.c
int		file_to_arr(char ***raw_map, char *path);

// check_file.c
int		check_file(char *str, char *data_type);

// get_textures.c
int		get_textures(t_map *map_data, char **raw_map);
int		finde_line(char *direction, char **raw_map, int *i);
char	**get_line_content(char *raw_line);
char	*cpy_line(char *dest, char *src, int len);
int		get_data(t_map *map_data, char *raw_line);

// get_ea.c
int		get_ea(t_map *map_data, char **raw_map);

// get_no.c
int		get_no(t_map *map_data, char **raw_map);

// get_so.c
int		get_so(t_map *map_data, char **raw_map);

// get_we.c
int		get_we(t_map *map_data, char **raw_map);

// get_ceiling.c
int		get_ceiling(t_map *map_data, char **raw_map);

// get_floor.c
int		get_floor(t_map *map_data, char **raw_map);

// remove_letter.c
void	remove_letter(char **line_content, char letter);

// get_map.c
int		get_map(t_map *map_data, char **raw_map);

// check_wall_horizontal.c
int		check_wall_horizontal(char **raw_map);

// check_wall_vertical.c
int		check_wall_vertical(char **raw_map);

// map_to_arr.c
int		map_to_arr(char **raw_map, t_map *map_data, int start_map);

// check_map.c
int		check_map(char **raw_map);

// malloc_map.c
int		malloc_map(char ***map, int map_height, int map_width);

// get_textures_utils.c
void	free_textures(t_map *map_data);


#endif
