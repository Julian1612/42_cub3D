/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:16 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/12 19:32:30 by lorbke           ###   ########.fr       */
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

# define WIDTH 800
# define HEIGHT 800
# define NOT_SET -1
# define ERROR -1
# define SUCCESS 0
# define MINIMAP_WALL_SIZE 30
# define FLOOR '0'
# define WALL '1'
# define FPS 60
# define OBJ_COUNT 4
# define DOOR_CLOSED 'D'
# define DOOR_OPEN 'd'
# define ENEMY 'E'
# define FPS 60

/* ************************************************************************** */
/* ENUMS																	  */
/* ************************************************************************** */

enum	e_obj_type
{
	DECOR_NON_PERM,
	DECOR_PERM,
	WEAPON,
	COIN,
};

/* ************************************************************************** */
/* TYPEDEFS																	  */
/* ************************************************************************** */

typedef struct s_door
{
	bool			open;
	double			last_action;
	int				x;
	int				y;
}	t_door;

typedef struct s_object
{
	t_vec			pos;
	t_tex			*tex;
	enum e_obj_type	type;
}	t_object;

typedef struct s_minimap
{
	t_vec			pos;
	double			width;
	double			height;
	int				visible;
	mlx_image_t		*minimap_walls;
	mlx_image_t		*player;
	mlx_image_t		*walls;
	mlx_image_t		*view_dir;
}	t_minimap;

typedef struct s_enemy	t_enemy;

typedef struct s_map
{
	char		**arr;
	t_tex		*textures[4]; // muss noch erhöht werden auf texturen von gegnern und türen
	t_door		*doors;
	int			door_count;
	t_object	*objects;
	int			obj_count;
	t_enemy		*enemies;
	int			enemy_count;
	t_hexcolor	ceiling_color;
	t_hexcolor	floor_color;
	int			width;
	int			height;
}	t_map;

typedef struct s_start_screen
{
	bool			active;
	mlx_image_t		*background;
	mlx_image_t		*img_start_button;
	mlx_image_t		*img_exit_button;
	mlx_image_t		*img_soldier_up;
	mlx_image_t		*img_soldier_down;
	mlx_texture_t	*start_button;
	mlx_texture_t	*exit_button;
	mlx_texture_t	*soldier_down;
	mlx_texture_t	*soldier_up;
}	t_start_screen;

// @note items might be added here
typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img_world;
	mlx_image_t		*img_hud;
	t_map			map;
	t_minimap		minimap;
	t_player		player;
	t_enemy			*enemies;
	t_start_screen	start_screen;
}	t_game;

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

// error
void			errexit_msg(char *msg);
void			errexit_mlx_errno(void);

// math
int				coor_to_pixel(int width, int x, int y);
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
bool			collision_is_true(double x, double y,
					t_map *map, int enemy_num);
int				collision_is_enemy(double x, double y,
					t_map *map, int enemy_num);

// time
double			get_fps_mult(double delta_time, int fps);
bool			is_next_frame(double *delta_time);
bool			is_cooldown(void);

// start_screen
int				initialize_start_screen(t_game *game);
void			draw_background(t_start_screen *start_screen);

#endif
