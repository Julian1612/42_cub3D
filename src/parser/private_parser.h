/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_parser.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:13:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/14 18:39:39 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_PARSER_H
# define PRIVATE_PARSER_H
# include "../cub3D.h"

/* check_for_bonus_textures.c */
int				check_for_bonus_texture(t_map *map_data, char *line,
					int *error);

/* check_for_map.c */
int				check_for_map(t_map *map_data, char *line, int fd, int *error);

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
int				error_textures_2(int error_code, t_map *map_data);
int				error_textures(int error_code, t_map *map_data);
int				error_get_map(int error_code, t_map *map_data);
void			free_parser_data(t_map *map_data);

/* get_file_data.c */
int				get_file_data(t_map *map_data, char *cub_file_path);

/* init_player_position.c */
int				init_player_position(t_game *game);

/* init_struct.c */
int				init_sprite_position(t_game *game);

/* parser.c */
int				parser(int *argc, char **argv, t_game *game);
int				check_data_type(char *path, char *data_type);
int				check_file(char *cub_file_path, char *data_type);

/* parser_utils_0.c */
void			init_struct_null(t_map *map_data);
int				is_all_digit(char **str);
bool			contains_only_spaces(const char *str);
int				check_for_new_line(char **splitted_str, int *error);
void			clear_buffer(char **line);

/* parser_utils_1.c */
void			remove_last_char(char *str);
int				clear_mem(char **line);
char			*ft_strjoin_free_s1(char const *s1, char const *s2);
int				check_pos_in_map(t_map *map, int i, int j);
void			init_door(t_map *map_data, int i, int j, int count_doors);

#endif
