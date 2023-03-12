/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_parser.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:13:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/12 15:31:43 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_PARSER_H
# define PRIVATE_PARSER_H
# include "../cub3D.h"

/* check_args.c */
int		check_args(int *argc, char **argv);

/* check_file.c */
int		check_file(char *cub_file_path, char *data_type);

/* check_for_bonus_textures.c */
int		check_for_map(t_map *map_data, char *line, int fd);

/* check_for_map.c */
int		check_for_map(t_map *map_data, char *line, int fd);

/* check_for_rgb.c */
int		check_for_rgb(t_map *map_data, char *line);

/* check_for_textures.c */
int		check_for_texture(t_map *map_data, char *line);
char	*cpy_line(char **des, char *src, int len);

/* error_messages.c */
void	error_message(int error_code);
void	error_textures(int error_code);
void	error_get_map(int error_code);

/* get_file_data.c */
int		get_file_data(t_map *map_data, char *cub_file_path);

/* parser.c */
int		parser(int *argc, char **argv, t_map *map_data);

#endif
