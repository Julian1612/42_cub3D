/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_parser.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:13:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/07 12:55:40 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_PARSER_H
# define PRIVATE_PARSER_H
# include "../cub3D.h"
# define NBR_B_TEXTURES 3
# define CHAR_DOOR 'D'
# define CHAR_BARREL 'B'
# define CHAR_ENEMY 'E'

/* check_for_bonus_textures.c */
int				check_for_bonus_texture(t_map *map_data, char *line);

/* check_for_map.c */
int				check_for_map(t_map *map_data, char *line, int fd);

/* check_for_rgb.c */
int				check_for_rgb(t_map *map_data, char *line, int *error);

/* check_for_textures.c */
int				check_for_texture(t_map *map_data, char *line, int *error);
char			*cpy_line(char **des, char *src, int len);

/* check_map.c */
int				check_map(t_map *map_data);

/* check_textures.c */
int				check_mandatory_textures(t_map *map_data);
int				check_bonus_textures(t_map *map_data);

/* error_messages.c */
int				error_message(int error_code, t_map *map_data);
int				error_textures(int error_code, t_map *map_data);
int				error_get_map(int error_code, t_map *map_data);

/* get_file_data.c */
int				get_file_data(t_map *map_data, char *cub_file_path);

/* init_player_position.c */
int				init_player_position(t_map *map_data, t_player *player_pos);

/* parser.c */
int				parser(int *argc, char **argv, t_map *map_data, t_player *player_pos);
int				check_data_type(char *path, char *data_type);
int				check_file(char *cub_file_path, char *data_type);

/* utils.c */
void			init_struct_null(t_map *map_data);
unsigned int	convert_to_hexcode(unsigned char r, unsigned char g,
					unsigned char b, unsigned char a);
int				get_map_size(t_map *map_data);

#endif
