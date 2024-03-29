/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:16 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/15 00:39:54 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "types.h"
# include "player.h"
# include "../libraries/mlx42/include/MLX42/MLX42.h" // mlx typedefs

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
# define MINIMAP_WALL_SIZE 30
# define DOOR_CLOSED 'D'
# define DOOR_OPEN 'd'
# define ENEMY 'F'
# define EXIT 'X'
# define SOUND_MAX 10

/* ************************************************************************** */
/* ENUMS																	  */
/* ************************************************************************** */

enum	e_sound_id
{
	SOUND_START,
	SOUND_START_CLICK,
	SOUND_GAME,
	SOUND_WIN,
	SOUND_LOSE,
	SOUND_GUN,
	SOUND_DOOR,
	SOUND_ENEMY_DIE,
	SOUND_PLAYER_DAMAGE,
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

typedef struct s_enemy	t_enemy;

typedef struct s_map
{
	char		**arr;
	t_tex		textures[LAST];
	t_door		*doors;
	int			door_count;
	t_enemy		*enemies;
	int			enemy_count;
	t_hexcolor	ceiling_color;
	t_hexcolor	floor_color;
	int			width;
	int			height;
}	t_map;

typedef struct s_hud
{
	mlx_image_t		*img;
	mlx_image_t		*img_str;
}	t_hud;

typedef struct s_screen
{
	bool			active;
	mlx_image_t		*img;
	t_frame			frame;
}	t_screen;

// @note items might be added here
typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img_world;
	mlx_image_t		*img_minimap;
	t_hud			hud;
	t_screen		start;
	t_screen		lose;
	t_screen		win;
	t_map			map;
	t_player		player;
	t_enemy			*enemies;
	int				sound_id[SOUND_MAX];
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
bool			collision_is_true(double x, double y,
					t_map *map, int enemy_num);
int				collision_is_enemy(double x, double y,
					t_map *map, int enemy_num);

// time
void			set_next_frame(t_frame *frame, enum e_tex_id start,
					int frame_count);
double			get_fps_mult(double delta_time, int fps);
bool			is_next_frame(double *delta_time);
bool			is_cooldown(void);

// sound
void			sound_play(int *sound_id, char *path, char *cmd);
void			sound_stop(int sound_id);
void			sound_stop_all(int *sound_id);

#endif
