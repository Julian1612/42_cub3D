/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:16 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/14 23:40:11 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "types.h"
# include "player.h"
# include "../libraries/mlx/include/MLX42/MLX42.h" // mlx typedefs

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# ifndef DEBUG
#  define DEBUG 0
# endif

# define WIDTH 1200
# define HEIGHT 800
# define NOT_SET -1
# define ERROR -1
# define SUCCESS 0
# define FLOOR '0'
# define WALL '1'
# define FPS 60

/* ************************************************************************** */
/* TYPEDEFS																	  */
/* ************************************************************************** */

typedef struct s_map
{
	char		**arr;
	t_tex		textures[LAST];
	t_hexcolor	ceiling_color;
	t_hexcolor	floor_color;
	int			width;
	int			height;
}	t_map;

// @note items might be added here
typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img_world;
	t_map			map;
	t_player		player;
}	t_game;

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

// error
void			errexit_msg(char *msg);
void			errexit_mlx_errno(void);

// math
uint32_t		coor_to_pixel(uint32_t width, int x, int y, uint32_t height);
double			rotate_x(double x, double y, double angle);
double			rotate_y(double x, double y, double angle);
int				ft_abs(int n);
double			get_dist_of_vecs(t_vec *a, t_vec *b);

// utils
t_hexcolor		convert_to_hexcode(unsigned char r, unsigned char g,
					unsigned char b, unsigned char a);

// initialize
int				initialize_mlx_data(t_game *game);

// collision
bool			collision_is_true(double x, double y, t_map *map);

// time
double			get_fps_mult(double delta_time, int fps);
bool			is_next_frame(double *delta_time);

#endif
