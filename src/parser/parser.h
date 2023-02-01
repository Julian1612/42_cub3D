/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:13:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/01 17:20:55 by jschneid         ###   ########.fr       */
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
int		map_to_arr(char **raw_map, char *path);

// check_file.c
int		check_file(char **argv);

#endif
