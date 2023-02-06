/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:13:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/06 14:02:24 by jschneid         ###   ########.fr       */
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
	char			*s;
	char			*f;
	char			**map;
}				t_map;

// parser.c
int		parser(int *argc, char **argv, t_map *map_data);

// error_message.c
void	error_message(int error_code);

// map_to_arr.c
int		map_to_arr(char ***raw_map, char *path);

// check_file.c
int		check_file(char *str, char *data_type);

// get_textures.c
int		get_textures(t_map *map_data, char **raw_map);
int		finde_line(char *direction, char **raw_map, int *i);
char	**get_line_content(char *raw_line);
// int		get_path(t_map *map_data, char **line_content);
char	*cpy_line(char *dest, char *src, int len);
int		get_data(t_map *map_data, char *raw_line);

// get_ea.c
int		get_ea(t_map *map_data, char **raw_map);

// get_no.c
int		get_no(t_map *map_data, char **raw_map);

// get_so.c
int		get_so(t_map *map_data, char **raw_map);

// get_we.c
int 	get_we(t_map *map_data, char **raw_map);

#endif
